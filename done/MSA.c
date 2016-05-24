#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int maxCont(int *pt, int n) {

	int maxGlobal = pt[0],maxStreak = pt[0];
	int i;

	for(i=1;i<n;i++) {
		if(pt[i] > maxStreak + pt[i])
			maxStreak = pt[i];
		else
			maxStreak = maxStreak + pt[i];

		if(maxGlobal < maxStreak)
			maxGlobal = maxStreak;
	}

	return maxGlobal;
}

int maxNCont(int *pt, int n) {
	int c=0,i,neg=0;
	for(i=0;i<n;i++) {
		if(pt[i] > 0) 
			c = c + pt[i];
		else
			neg++;
	}

	if(neg == n) {
		c = pt[0];
		for(i=1;i<n;i++) {
			if(c < pt[i])
				c = pt[i];
		}
	}

	return c;
}

int main() {

	int tc;
	scanf("%d", &tc);

	int **mn = (int **)malloc(tc*sizeof(int *));
	int *ele = (int *)malloc(tc*sizeof(int));


	int i, j;
	for(i=0;i<tc;i++) {
		scanf("%d", &ele[i]);
		mn[i] = (int *)malloc(ele[i]*sizeof(int));
		for(j=0;j<ele[i];j++) {
			scanf("%d", &mn[i][j]);
		}
	}

	int mc, mnc;

	for(i=0;i<tc;i++) {
		mc = maxCont(mn[i], ele[i]);
		mnc = maxNCont(mn[i], ele[i]);
		printf("%d %d\n", mc, mnc);
	}

	return 0;
}