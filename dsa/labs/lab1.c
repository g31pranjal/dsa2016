#include <stdio.h>

int main(int argc, int **argv) {
	int n = atoi(argv[1]);
	int *ptr[n];
	int *row1, *row2;

	ptr[0] = (int*)calloc(1, sizeof(int));
	row1 = ptr[0];

	row1[0] = 1;

	int i = 1;

	for(;i<sizeof(ptr)/8;i++) {
		row1 = ptr[i-1];
		ptr[i] = (int*)calloc(i+1, sizeof(int));
		row2 = ptr[i];

		row2[0] = 1;

		int k=1;
		for(;k<i;k++) {	
			row2[k] = row1[k] + row1[k-1];
		}

		row2[i] = 1;

		int z,p;

		for(p=i;p<n;p++) {
			printf("\t");
		}



		for(z=0;z<i;z++) {
			printf("%d \t\t", row1[z]);
		}
		printf("\n");
	}

	int z;
	for(z=0;z<n;z++) {
		printf("%d \t\t", row2[z]);
	}
}