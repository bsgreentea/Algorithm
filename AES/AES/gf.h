#pragma once

// irreducible polynomial
const unsigned int IP = 0x14D;

int add(int a, int b);
int sub(int a, int b);
unsigned char multi(unsigned int a, unsigned int b);
int bit_length(unsigned int bin_num);
unsigned int inverse(unsigned int x);