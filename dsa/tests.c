#include <stdio.h>
#include <stdlib.h>

int main() {
	char p[50];
	int i=0, a, b, resp;

	for(i=0;i<50;i++) {
		p[i] = '\0';
	}

	resp = scanf("%d %d", &a, &b);

	printf("%d\n", resp);
}