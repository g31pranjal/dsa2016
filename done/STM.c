#include <stdlib.h>
#include <math.h>
#include <stdio.h>


int calcProf(int *pt, int n) {
	//printf("value of n %d\n", n);

	long prof = 0, partProf = 0;
	int i, j, li, max;

	// number of highest numbers there shall be
	for(i=0;i<n;) {
		//printf("i:%d\n", i);
		partProf = 0;
		max = pt[i];
		li = i;
		for(j=i+1;j<n;j++) {
			//printf("j:%d\n", j);
			if(max <= pt[j]) {
				li = j;
				max = pt[j];
			}
		}

		//printf("max : %d, at %d\n", max, li);

		for(j=i;j<li;j++) {
			partProf = partProf + (max - pt[j]);
		} 
		pt[li] = -1;
		i = li + 1;

		prof += partProf;

	}

	printf("%ld\n", prof);

	return 0;

}


int main() {
	int tc=0,i,j;
	scanf("%d", &tc);
	
	int **mn, *nele;
	mn = (int **)malloc(tc*sizeof(int *));
	nele = (int *)malloc(tc*sizeof(int));

	for(i=0;i<tc;i++) {
		scanf("%d", &nele[i]);
		mn[i] = (int *)malloc(nele[i]*sizeof(int));
		for(j=0;j<nele[i];j++) {
			scanf("%d", &mn[i][j]);
		}
	}

	for(i=0;i<tc;i++) {
		calcProf(mn[i], nele[i]);
	}





	return 0;
}