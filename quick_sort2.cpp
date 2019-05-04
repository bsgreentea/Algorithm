#include <cstdio>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quick_sort(int* arr, int start, int end) {
	
	if (start >= end) return;

	int pivot = start;
	int left = pivot + 1, right = end;

	while (left <= right) {

		while (left <= end && arr[left] <= arr[pivot]) left++;
		while (right > start && arr[right] >= arr[pivot]) right--;

		if (left > right)
			swap(&arr[right], &arr[pivot]);
		else
			swap(&arr[left], &arr[right]);
	}

	quick_sort(arr, start, right - 1);
	quick_sort(arr, right + 1, end);
}

int main() {

	int arr[] = { 9,8,7,6,5,4,3,2,1 };
	
	quick_sort(arr, 0, 8);

	for (int i = 0; i < 9; i++) {
		printf("%d ", arr[i]);
	}puts("");
}