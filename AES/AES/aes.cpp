#include "aes.h"
#include "gf.h"
#include <cstdio>

// round constants 생성
void AES::make_rc() {

	for (int i = 1; i < 10; i++) {

		rc[i] = multi((unsigned int)rc[i - 1], 2);
	}
}

// s-box 생성
// 행렬 연산으로 구현
void AES::make_s_box() {

	for (unsigned char i = 0; i < 16; i++) {
		for (unsigned char j = 0; j < 16; j++) {

			unsigned char b1[8] = { 0, };
			unsigned char b2[8] = { 0, };

			// 역원 구하기
			unsigned char inv = (unsigned char)inverse((unsigned int)(i * 16 + j));

			// 역원을 비트 단위로 나누기
			for (unsigned char ii = 0; ii < 8; ii++) {
				b1[ii] = (1 << ii) & inv ? 1 : 0;
			}

			for (unsigned char ii = 0; ii < 8; ii++) {

				// 한 번에 계산하기
				// b2[ii] = b1[ii] ^ b1[(ii + 4) % 8] ^ b1[(ii + 5) % 8] ^ b1[(ii + 6) % 8] ^ b1[(ii + 7) % 8] ^ s_box_constant[ii];

				// 행렬 계산
				for (unsigned char jj = 0; jj < 8; jj++) {
					b2[ii] ^= matrix[ii][jj] * b1[jj];
				}
				b2[ii] ^= s_box_constant[ii];
			}

			// 값 할당
			s_box[i][j] = 0;
			for (unsigned char ii = 0; ii < 8; ii++) {
				s_box[i][j] |= (b2[ii] << ii);
			}
		}
	}

	/* // SBOX TEST
	puts("SBOX TEST");
	for (unsigned char i = 0; i < 16; i++) {
		for (unsigned char j = 0; j < 16; j++) {
			printf("%02X ", s_box[i][j]);
		}puts("");
	}puts("\n\n");
	*/
}

// inverse s-box 만들기
// 행렬 연산 없이 s-box로부터 구현
void AES::make_inv_sbox() {

	for (unsigned char i = 0; i < 16; i++) {
		for (unsigned char j = 0; j < 16; j++) {
			
			unsigned char tmp = s_box[i][j];

			inv_s_box[tmp >> 4][tmp % 16] = i * 16 + j;
		}
	}
}

// round function
void AES::round_function(unsigned char from[4], unsigned char round_num) {

	unsigned char temp = from[0];

	from[0] = sub_byte(from[1]) ^ rc[round_num];
	from[1] = sub_byte(from[2]);
	from[2] = sub_byte(from[3]);
	from[3] = sub_byte(temp);
}

// key expansion
void AES::key_expansion() {

	for (unsigned char j = 4; j < 44; j++) {

		if (j % 4 == 0) {

			unsigned char temp[4] = { 0 };

			for (int i = 0; i < 4; i++) {
				temp[i] = expanded_key[i][j - 1];
			}

			round_function(temp, (j / 4) - 1);

			for (int i = 0; i < 4; i++) {
				expanded_key[i][j] = temp[i] ^ expanded_key[i][j - 4];
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				expanded_key[i][j] = expanded_key[i][j - 1] ^ expanded_key[i][j - 4];
			}
		}
	}

	puts("KEY EXPANSION");
	for (int j = 0; j < 44; j++) {
		if (j % 4 == 0) printf("ROUND %d: ", j / 4);
		for (int i = 0; i < 4; i++) {
			printf("%02X ", expanded_key[i][j]);
		}
		if (j % 4 == 3) puts("");
	}
}

// add round key
void AES::add_round_key(unsigned char from[4][4], unsigned char round_num) {

	for (unsigned char i = 0; i < 4; i++) {
		for (unsigned char j = 0; j < 4; j++) {
			from[i][j] = from[i][j] ^ expanded_key[i][j + (round_num * 4)];
		}
	}

	printf("AR: ");
	for (unsigned char i = 0; i < 4; i++) {
		for (unsigned char j = 0; j < 4; j++) {
			printf("%02X ", from[j][i]);
		}
	}puts("");
}

// s-box 값 가져오기
unsigned char AES::sub_byte(unsigned char num) {
	return s_box[num >> 4][num % 16];
}

// s-box 값으로 변환
void AES::sub_bytes(unsigned char from[4][4]) {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			from[i][j] = sub_byte(from[i][j]);
		}
	}

	printf("SB: ");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%02X ", from[j][i]);
		}
	}puts("");
}

// shift rows
void AES::shift_rows(unsigned char from[4][4]) {

	unsigned char temp[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[i][j] = from[i][j];
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			from[i][j] = temp[i][(j + i) % 4];
		}
	}

	printf("SR: ");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%02X ", from[j][i]);
		}
	}puts("");
}

// mix columns
void AES::mix_col(unsigned char from[4][4]) {

	unsigned char temp[4][4] = { 0, };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				temp[i][j] ^= multi(mix_mat[i][k], from[k][j]);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			from[i][j] = temp[i][j];
		}
	}

	printf("MC: ");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%02X ", from[j][i]);
		}
	}puts("");
}

/*

encryption 과정과 전체적으로 동일

s-box -> inverse s-box로 변경
shift 방향 수정
mix matrix -> inverse mix matrix로 변경

*/

unsigned char AES::inv_sub_byte(unsigned char num) {
	return inv_s_box[num >> 4][num % 16];
}

void AES::inv_sub_bytes(unsigned char from[4][4]) {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			from[i][j] = inv_sub_byte(from[i][j]);
		}
	}

	printf("SB: ");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%02X ", from[j][i]);
		}
	}puts("");
}

void AES::inv_shift_rows(unsigned char from[4][4]) {

	unsigned char temp[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[i][j] = from[i][j];
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			from[i][j] = temp[i][(j + 4 - i) % 4];
		}
	}

	printf("SR: ");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%02X ", from[j][i]);
		}
	}puts("");
}

void AES::inv_mix_col(unsigned char from[4][4]) {

	unsigned char temp[4][4] = { 0, };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				temp[i][j] ^= multi(inv_mix_mat[i][k], from[k][j]);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			from[i][j] = temp[i][j];
		}
	}

	printf("MC: ");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%02X ", from[j][i]);
		}
	}puts("");
}

void AES::print_rc() {
	printf("RC : ");
	for (int i = 0; i < 10; i++) {
		printf("%02X ", rc[i]);
	}
	puts("");
}

void AES::set_key(unsigned char key[4][4]) {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			expanded_key[i][j] = key[i][j];
		}
	}

	make_s_box();

	key_expansion();
}

// 암호화
void AES::encryption(unsigned char plain_text[4][4]) {

	puts("\nROUND 0\n");
	add_round_key(plain_text, 0);
	puts("");

	for (unsigned char round = 1; round < 10; round++) {

		printf("ROUND %d\n", (int)round);

		sub_bytes(plain_text);
		shift_rows(plain_text);
		mix_col(plain_text);
		add_round_key(plain_text, round);

		puts("");
	}

	printf("ROUND 10\n");
	sub_bytes(plain_text);
	shift_rows(plain_text);
	add_round_key(plain_text, 10);

	puts("");

	printf("CIPHER: ");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%02X ", plain_text[j][i]);
		}
	}puts("");
}

// 복호화
void AES::decryption(unsigned char cipher[4][4]) {

	make_inv_sbox();

	puts("\nROUND 0\n");
	add_round_key(cipher, 10);
	puts("");

	for (unsigned char round = 1; round < 10; round++) {

		printf("ROUND %d\n", (int)round);
		
		inv_shift_rows(cipher);
		inv_sub_bytes(cipher);
		add_round_key(cipher, 10 - round);
		inv_mix_col(cipher);

		puts("");
	}

	printf("ROUND 10\n");
	inv_shift_rows(cipher);
	inv_sub_bytes(cipher);
	add_round_key(cipher, 0);

	puts("");

	printf("DECRYPTED: ");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%02X ", cipher[j][i]);
		}
	}puts("");
}