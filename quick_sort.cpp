#include <cstdio>
#include <vector>
using namespace std;

// coded by my foot

const int random_divisor = 2;

vector<int> vt, res;

void quick_sort(vector<int>& vt, int sz) {

	vector<int> L, G;

	int pivot_idx = vt.size() / random_divisor;

	for (int i = 0; i < vt.size(); i++) {
		
		if (i == pivot_idx) {
			continue;
		}
		else if (vt[i] < vt[pivot_idx]) {
			L.push_back(vt[i]);
		}
		else if (vt[i] >= vt[pivot_idx]) {
			G.push_back(vt[i]);
		}
	}

	res[sz + L.size()] = vt[pivot_idx];

	if (L.size()) quick_sort(L, sz);
	if (G.size()) quick_sort(G, sz + L.size() + 1);

	return;
}

int main() {

	//freopen("input.txt", "r", stdin);
	
	printf("input array size : ");
	int n;
	scanf("%d", &n);

	vt.resize(n);
	res.resize(n);

	printf("\n---------------input numbers--------------\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &vt[i]);
	}

	puts("\n-----------------sorted!!-----------------");
	quick_sort(vt, 0);
	
	for (int i = 0; i < res.size(); i++) {
		printf("%d ", res[i]);
	}puts("");
}