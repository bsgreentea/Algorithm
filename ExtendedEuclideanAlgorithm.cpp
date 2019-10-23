#include <cstdio>

typedef long long ll;
typedef struct {
	ll x, y, gcd;
} info;

info x_gcd(ll x, ll y) {

	ll a[3] = { 1,0,x };
	ll b[3] = { 0,1,y };
	ll q, t[3];

	while (1) {

		// ���μҰ� �ƴ� ��� modular ���� 0�̴�.
		// �� ��� x * inverse = 1 mod y �� �����ϴ� inverse�� �������� �ʴ´�. 
		if (b[2] == 0) return { 0,0,0 };
		if (b[2] == 1) return { b[0],b[1],1 };

		q = a[2] / b[2];
		
		for (int i = 0; i < 3; i++) {
			t[i] = a[i] - q * b[i];
			a[i] = b[i];
		}
		for (int i = 0; i < 3; i++) b[i] = t[i];
	}
}

int main() {

	ll m, b;
	scanf("%lld %lld", &m, &b);

	info ret = x_gcd(m, b);
}