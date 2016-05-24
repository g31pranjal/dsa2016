#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main() {
	char** strar;

	int tc = 0, i=0;
	scanf("%d", &tc);

	strar = (char **)malloc(tc*(sizeof(char *)));

	for(i=0;i<tc;i++) {
		strar[i] = (char *)malloc(1024*sizeof(char));
		scanf("%s", strar[i]);
	}


	int len, j=0;
	char num1[500];

	for(i=0;i<500;i++) {
		num1 = '\0';
		num2 = '\0';		
	}

	for(i=0;i<tc;i++) {
		j=0;
		len = strlen(strar[i]);
		while(strar[i][j] >= 48 && strar[i][j] <= 57) {
			j++;
		}
		opr = strar[i][j];
		ln1 = j;
		ln2 = len - 1 - j;
		
	}

}