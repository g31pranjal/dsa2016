#include <stdlib.h>
#include <stdio.h>

int main() {
	int tc=0;
	scanf("%d", &tc);

	int arr[tc];

	int i=0;
	for(i=0;i<tc;i++) {
		scanf("%d", &arr[i]);
	}
	
	for(i=0;i<tc;i++) {
		printFCT(arr[i]);
	}

}

int printFCT(int num) {
	int arr[200],i=0, j=0;

	for(i=0;i<200;i++) {
		arr[i] = 0;
	}

	int c = 1;
	int s = 1;
	arr[0] = 1;
	int carry=0,tmp=0;

	for(i=c+1;i<=num;i++) {
		carry = 0;
		for(j=0;j<s;j++) {
			tmp = i*arr[j] + carry;
			arr[j] = tmp%10;
			carry = tmp/10;
		}
		while(carry != 0) {
			arr[s] = carry%10;
			s++;
			carry = carry/10;
		}

		int cmp = 0;
		
	}
	
	for(j=s-1;j>=0;j--) {
		printf("%d", arr[j]);
	}
	printf("\n");

}