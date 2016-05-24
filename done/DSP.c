#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main() {
	int n, k;
	scanf("%d %d", &n, &k);

	int i,count=0, j;
	int arr[n];

	for(i=0;i<n;i++) {
		scanf("%d", &arr[i]);
		arr[i] = arr[i]%k;
	}

	for(i=0;i<n;i++) {
		for(j=i+1;j<n;j++) {
			if(arr[i] + arr[j] == k || arr[i] + arr[j] == 0 ) {
				count++;
			}
		}
	}

	printf("%d\n", count);
}