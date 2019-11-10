#include "gf.h"

int add(int a, int b) {
	return a ^ b;
}

int sub(int a, int b) {
	return a ^ b;
}

// galois field multiplication
unsigned char multi(unsigned int a, unsigned int b) {

	unsigned char ret = 0;

	while (a && b) {

		if (b & 0x01) ret ^= a;

		if (a & 0x80)
			a = (a << 1) ^ IP;
		else a <<= 1;

		b >>= 1;
	}

	return ret;
}

int bit_length(unsigned int bin_num) {

	int ret = 0;

	while (bin_num) {
		bin_num >>= 1;
		ret++;
	}

	return ret;
}

// 역원 구하기
// IP == irreducible polynomial
unsigned int inverse(unsigned int x)
{
	unsigned int u1 = 0, u3 = IP, v1 = 1, v3 = x;

	while (v3 != 0) {
		unsigned int t1 = u1, t3 = u3;
		
		int bit_diff = bit_length(u3) - bit_length(v3);

		if (bit_diff >= 0) {
			t1 ^= v1 << bit_diff;
			t3 ^= v3 << bit_diff;
		}
		u1 = v1; u3 = v3;
		v1 = t1; v3 = t3;
	}

	if (u1 >= 0x100) u1 ^= IP;

	return u1;
}