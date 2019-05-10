#include <cstdio>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int* arr, int left, int right) {

	int pivot = arr[left];
	int i = left, j = right;

	while (i < j) {
		while (arr[j] > pivot) j--;
		while (i < j && arr[i] <= pivot) i++;
		swap(arr + i, arr + j);
	}

	arr[left] = arr[i];
	arr[i] = pivot;
	return i;
}

void quick_sort(int* arr, int left, int right) {

	if (left >= right) return;

	int pivot_index = partition(arr, left, right);

	quick_sort(arr, left, pivot_index - 1);
	quick_sort(arr, pivot_index + 1, right);
}

int main() {

	int arr[] = { 9,8,7,6,5,4,3,2,1 };

	quick_sort(arr, 0, 8);

	for (int i = 0; i < 9; i++) {
		printf("%d ", arr[i]);
	}puts("");
}