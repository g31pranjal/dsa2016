#include <stdlib.h>
#include <math.h>
#include <stdio.h>


int calcPalin(int num) {
	int i=0,nod=0;
	int arr[100];
	
	int tmp = num;
	while(tmp != 0) {
		nod++;
		tmp /= 10;
	}
	tmp = num;
	for(i=nod - 1;i>=0;i--) {
		arr[i] = tmp%10;
		tmp = tmp / 10;
	}

	int scaledprev = 0;
	int li=0,ri=0, k=0;

	int nodi = nod - 1;

	//printf("%d\n", nodi);



	for(i = nodi/2;i>=0;i--) {
		li = i;
		ri = nodi - i;

		if(arr[ri] > arr[li]) { 			// upper bound
			if(scaledprev == 1) {
				arr[ri] = arr[li];
				scaledprev = 0;
			}
			else {								// not scaled 
				if(li + 1 > nodi/2) {				// cannot be scaled
					arr[li] = arr[li] + 1;
					arr[ri] = arr[li];
					scaledprev = 1;
				}
				else {								// can be scaled
					arr[li+1] = arr[li+1] + 1;
					arr[ri-1] = arr[li+1];
					arr[ri] = arr[li];
					scaledprev = 0;
				}
			}
		}
		else if(arr[ri] < arr[li]) {	// lower bound
			arr[ri] = arr[li];
			scaledprev = 1;
		}
		else {							// equal
			scaledprev = 0;
		}

	}
	
	int sum=0;

	for(k=0;k<nod;k++) {
		sum = sum*10 + arr[k];
	}
	//printf("sum : %d\n", sum);
	if(sum == num)
		return calcPalin(num + 1);
	else
		return sum;

}


int main() {
	int n,i,num;
	scanf("%d", &n);
	int arr[n];
	for(i=0;i<n;i++) {
		arr[i] = -1;
	}

	for(i=0;i<n;i++) {
		scanf("%d", &num);
		arr[i] = calcPalin(num);
	}


	for(i=0;i<n;i++) {
		printf("%d\n", arr[i]);
	}
	
	return 0;

}