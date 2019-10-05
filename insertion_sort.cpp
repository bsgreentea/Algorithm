#include <cstdio>

void insertion_sort(int* arr, int n) {

	for (int i = 1; i < n; i++) {

		int key = arr[i];

		int j;
		for (j = i - 1; j >= 0; j--) {
			if (arr[j] > key) {
				arr[j + 1] = arr[j];
			}
			else break;
		}
		arr[j + 1] = key;
	}
}

int main() {

	int arr[5] = { 9,1,4,3,2 };

	insertion_sort(arr, 5);

	for (int i = 0; i < 5; i++)
		printf("%d ", arr[i]);

	puts("");
}