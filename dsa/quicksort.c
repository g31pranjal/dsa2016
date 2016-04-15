#include <stdio.h>
#include <stdlib.h>

void quicksort(int arr[], int p, int r) {
	int q = partition(arr, p, r);
	if(p != q) {
		quicksort(arr, p, q-1);
	}
	if(q != r) {
		quicksort(arr, q+1, r);
	}
}

int partition(int arr[], int p, int r) {
	int x = arr[r];
	int i = p-1;
	int j, t;
	for(j=p;j<r;j++) {
		if(arr[j] < x) {
			i = i+1;
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
	}
	t = arr[i+1];
	arr[i+1] = arr[r];
	arr[r] = t;

	return i+1;
}


int main() {

	int arr[10];

	int i=0;
	for(i=0;i<10;i++) {
		arr[i] = rand()%100;
	}

	for(i=0;i<10;i++) {
		printf("%d\t", arr[i]);
	}

	printf("\n");

	quicksort(arr, 0, sizeof(arr)/sizeof(int) - 1);

	for(i=0;i<10;i++) {
		printf("%d\t", arr[i]);
	}

}