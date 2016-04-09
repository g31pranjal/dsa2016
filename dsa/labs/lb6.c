#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wrdst wBlock;

struct wrdst{
	char word[50];
	int pageArray[100];
	int frq;
	int radix[50];
};

int addWBlock(int * wordCount, char *tkn, wBlock **st, int pgno, int * maxWordLength) {	
	wBlock *ref;

	ref = (wBlock*)malloc(sizeof(wBlock));
	strcpy(ref->word, tkn);
	ref->pageArray[ref->frq] = pgno;
	ref->frq += 1;

	if(strlen(tkn) > *maxWordLength) {
		*maxWordLength = strlen(tkn);
	}

	int i=0;
	for( i = 0; i<strlen(ref->word); i++){
		ref->radix[i] = ref->word[i] - 96; 
	}
	for( ;i<50; i++){
		ref->radix[i] = 0; 
	}
	st[*wordCount] = ref;
	*wordCount += 1;

	return 0;
}


int updateWBlock(int offset, wBlock **st, int pgno) {
	wBlock *ref = st[offset];
	
	if(ref->pageArray[(ref->frq) - 1] != pgno){
		ref->pageArray[ref->frq++]= pgno;
	}

	return 0;
}


char * toLowerCase(char *tkn) {
	int i;
	for( i = 0; i<strlen(tkn); i++){
		tkn[i] = tolower(tkn[i]);
	}
	return tkn;			
}


int countingSort(wBlock **a, wBlock **b, int d, int wordnum) {
	int i;
	int buffer[27];
	
	for(i=0;i<27;i++){
		buffer[i]=0;
	}

	for(i=0;i<wordnum;i++){
		buffer[a[i]->radix[d]]++;	
	}

	for(i=1;i<27;i++){
		buffer[i]+=buffer[i-1];
	}
	for(i=wordnum-1;i>=0;i--){
		b[buffer[a[i]->radix[d]] - 1]= a[i];
		buffer[a[i]->radix[d]]--;
	}

	return 0;

}


wBlock ** radixSort(wBlock **st, int wordnum, int maxWordLength){
	wBlock **a = st;
	wBlock **b = (wBlock **)malloc(wordnum*sizeof(wBlock *));	
	wBlock **tmp;

	int i;
	for(i=maxWordLength-1;i>=0;i--){
		countingSort(a, b, i, wordnum);
		tmp = b;
		b = a;
		a = tmp;
	}	
	return a;
		
}


int printIndex(wBlock **a, int wordnum) {
	int k=0, l=0;
	for(k=0;k<wordnum;k++) {
		printf("%s", a[k]->word);
		for(l=0;l<a[k]->frq;l++) {
			printf(" %d", a[k]->pageArray[l]);
			if(l+1 != a[k]->frq) {
				printf(",");
			}
		}		
		printf("\n");
	}
	return 0;
}


int main(){

	// Open the file in read mode !
	FILE *fileHandle= fopen("test.txt", "r");
	
	int pgno, wrdCount = 0, maxWordLength=0, interrupt = 0;
	char *line= NULL, *tkn;
	wBlock ** init = (wBlock **)malloc(5000*sizeof(wBlock *));

	size_t length = 0;
	
	int i;

	do {
		getline(&line, &length, fileHandle);
		if(strtol(line, NULL, 0) != 0){
			pgno = atoi(line);
		}
		else{
			tkn = strtok(line," \t\n{}[]|:;'<,>.?/1234567890-+'"); 
			while(tkn != NULL) {
				tkn = toLowerCase(tkn);
				interrupt = 0;
				for(i=0;i<wrdCount;i++) {
					if(strcmp(init[i]->word, tkn) == 0) {
						updateWBlock(i, init, pgno);
						interrupt = 1;
						break;					
					}
				}

				if(interrupt == 0) {
					addWBlock(&wrdCount, tkn, init, pgno, &maxWordLength);
				}
				
				tkn = strtok(NULL, " \t\n{}[]|:;'<,>.?/1234567890-+'");
			}		 
		}
	} while(!feof(fileHandle));
	
	init = radixSort(init, wrdCount, maxWordLength);

	printIndex(init, wrdCount);

	return 0;
}