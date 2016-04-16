#include <stdio.h>
#include <stdlib.h>

void mergesort(int arr[], int p, int r) {

	if(p<r) {
		int q = (p+r)/2;

		mergesort(arr, p, q);
		mergesort(arr, q+1, r);

		merge(arr, p, q, r);
	}


	
}

void merge(int arr[], int p, int q, int ri) {
	int np = q - p + 1;
	int nq = ri - (q + 1) + 1;

	int l[np], r[nq], i, m, n;

	for(i=0;i<np;i++) {
		l[i] = arr[p+i];
	}

	for(i=0;i<nq;i++) {
		r[i] = arr[q+1+i];
	}

	m=0;
	n=0;
	for(i=p;i<=ri;i++) {
		if(m == np)
			arr[i] = r[n++];
		else if(n == nq)
			arr[i] = l[m++];
		else {
			if(l[m] < r[n])
				arr[i] = l[m++];
			else
				arr[i] = r[n++];
		}
	}
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

	mergesort(arr, 0, sizeof(arr)/sizeof(int) - 1);

	for(i=0;i<10;i++) {
		printf("%d\t", arr[i]);
	}
}