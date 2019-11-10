#include <cstdio>
#include "aes.h"
#include <fstream>
#include <iostream>
using namespace std;

unsigned char plain[16];
unsigned char plain_text[4][4];
unsigned char key[16];
unsigned char key2[4][4];

void print_condition();

int main() {

	AES aes;

	// round constatns 생성 후 출력
	aes.print_rc();

	// plain text, key 출력
	print_condition();

	puts("<------ ENCRYPTION ------>\n");

	// key 설정
	aes.set_key(key2);
	// 암호화
	aes.encryption(plain_text);

	char buf[100];

	int k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			buf[k++] = plain_text[j][i];
		}
	}

	ofstream outfile1("cipher.bin", ofstream::binary);

	outfile1.write(buf, 16);
	outfile1.close();

	puts("\n<------ DECRYPTION ------>\n");
	// 복호화
	aes.decryption(plain_text);

	k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			buf[k++] = plain_text[j][i];
		}
	}

	ofstream outfile2("decrypt.bin", ofstream::binary);

	outfile2.write(buf, 16);
	outfile2.close();

	system("pause");
	_sleep(100000);
	return 0;
}

void print_condition(){

	freopen("plain.bin", "r", stdin);
	for (int i = 0; i < 16; i++)
		scanf("%02X ", plain + i);

	printf("PLAIN: ");
	for (int i = 0; i < 16; i++) {
		printf("%02X ", plain[i]);
	}puts("");

	freopen("key.bin", "r", stdin);
	for (int i = 0; i < 16; i++)
		scanf("%02X ", key + i);

	printf("KEY: ");
	for (int i = 0; i < 16; i++) {
		printf("%02X ", key[i]);
	}puts("\n");

	int idx = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			plain_text[j][i] = plain[idx++];

	idx = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			key2[j][i] = key[idx++];
}