#include <stdlib.h>
#include <math.h>
#include <stdio.h>


int cRec(int max, int rc, int *pt, int ncurr, int ctr) {
	int c=0,i;


	if(rc == max) {
		//printf("%d, %d\n", rc,  ctr);
		return 1; 
	}
	else {
		for(i=ctr;i<ncurr;i++) {
			if(max >= rc + pt[i]) {
				//printf("%d, %d, %d\n", rc, pt[i], i);
				c +=  cRec(max, rc + pt[i], pt, ncurr, i);
			}
		}
	}

	return c;
}


int main() {
	int n,ncurr,i;
	int *curr;
	curr = (int *)malloc(ncurr*sizeof(int));

	scanf("%d %d", &n, &ncurr);

	for(i=0;i<ncurr;i++) {
		scanf("%d", &curr[i]);
	}

	printf("%d\n", cRec(n, 0, curr, ncurr, 0));
}