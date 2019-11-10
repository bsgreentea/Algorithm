#pragma once

class AES {

private:

	// round constants
	unsigned char rc[10] = { 0x01 };
	// s-box ����
	unsigned char s_box[16][16];
	// inverse s-box
	unsigned char inv_s_box[16][16];

	// round key ���� (round 0 ~ round 10)
	unsigned char expanded_key[4][44];
	
	// sbox ���
	// 0��° ��Ʈ���� 7��° ��Ʈ ��
	const unsigned char s_box_constant[8] = { 1,0,1,0,1,0,0,0 };

	// for creating sbox
	const unsigned char matrix[8][8] = {

		1,0,0,0,1,1,1,1,
		1,1,0,0,0,1,1,1,
		1,1,1,0,0,0,1,1,
		1,1,1,1,0,0,0,1,
		1,1,1,1,1,0,0,0,
		0,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,0,
		0,0,0,1,1,1,1,1
	};

	// AES Mix Columns
	const unsigned char mix_mat[4][4] = {
		0x02, 0x03, 0x01, 0x01,
		0x01, 0x02, 0x03, 0x01,
		0x01, 0x01, 0x02, 0x03,
		0x03, 0x01, 0x01, 0x02
	};

	// AES Inverse Mix Columns
	const unsigned char inv_mix_mat[4][4] = {
		0x0E, 0x0B, 0x0D, 0x09,
		0x09, 0x0E, 0x0B, 0x0D,
		0x0D, 0x09, 0x0E, 0x0B,
		0x0B, 0x0D, 0x09, 0x0E
	};

	void make_rc();
	void make_s_box();
	void make_inv_sbox();
	void round_function(unsigned char from[4], unsigned char round_num);
	void key_expansion();
	
	void add_round_key(unsigned char from[4][4], unsigned char round_num);

	// encryption
	unsigned char sub_byte(unsigned char num); // sbox�� ��ȯ
	void sub_bytes(unsigned char from[4][4]); // 4x4 sbox������ ��ȯ
	void shift_rows(unsigned char from[4][4]); // shitr rows
	void mix_col(unsigned char from[4][4]); // mix columns

	// decryption
	unsigned char inv_sub_byte(unsigned char num);
	void inv_sub_bytes(unsigned char from[4][4]);
	void inv_shift_rows(unsigned char from[4][4]);
	void inv_mix_col(unsigned char from[4][4]);

public:

	AES() {
		make_rc();
	}

	void print_rc(); // round constants ���
	void set_key(unsigned char key[4][4]); // key setting

	void encryption(unsigned char plain_text[4][4]); // ��ȣȭ
	void decryption(unsigned char cipher[4][4]); // ��ȣȭ
};