#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int stepIns(int *pt, int size) {
	int i,j;
	int res = pt[size-1];

	for(i=size-2;i>=0;i--) {
		if(pt[i]>res) {
			pt[i+1] = pt[i];
		}
		else 
			break;

		for(j=0;j<size;j++) {
			printf("%d ", pt[j]);
		}
		printf("\n");
	}

	pt[i+1] = res;


	for(j=0;j<size;j++) {
		printf("%d ", pt[j]);
	}
	printf("\n");

	return 0;
}

int main() {
	int size = 0,i;
	scanf("%d", &size);

	int *arr = (int *)malloc(size*sizeof(int));
	for(i=0;i<size;i++) {
		scanf("%d", &arr[i]);
	}

	stepIns(arr, size);

	return 0;
}
