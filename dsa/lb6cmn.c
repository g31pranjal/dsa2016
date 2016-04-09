#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DELIM " .,:;1234567890\n"
#define NUMKEY 27

typedef struct WordStructure wordst;

struct WordStructure{
	char word[50];
	int page[100];
	int frequency;
	int code[50];
};



void countingSort(wordst **a, wordst **b, int d, int wordnum) {
	//printf("\n\nthis is counting sort !\n");
	int i;
	int c[NUMKEY];
	
	for(i=0;i<NUMKEY;i++){
		c[i]=0;
	}

	for(i=0;i<wordnum;i++){
		//printf("code : %d, %s\n", a[i]->code[d], a[i]->word );		
		c[a[i]->code[d]]++;	
	}

	for(i=1;i<NUMKEY;i++){
		c[i]+=c[i-1];
	}
	for(i=wordnum-1;i>=0;i--){

		//printf("%d, \n", c[a[i]->code[d]]);
		b[c[a[i]->code[d]] - 1]= a[i];
		c[a[i]->code[d]]--;
	}

	int ac, bc;

	for(ac=0;ac < wordnum;ac++) {
		//printf("%s, ", a[ac]->word);
	}
	//printf("\n");
	for(bc=0;bc < wordnum;bc++) {
		//printf("%s, ", b[bc]->word);
	}
}


void radixSort(wordst **st, int wordnum, int maxWordLength){
	wordst **a = st;
	wordst **b = (wordst **)malloc(wordnum*sizeof(wordst *));	
	wordst **tmp;

	int i;
	for(i=maxWordLength-1;i>=0;i--){
		countingSort(a, b, i, wordnum);
		tmp = a;
		a = b;
		b = tmp;
		//printf("a : %x\tb : %x\n", a, b);
	}	


	int k=0, l=0;
	for(k=0;k<wordnum;k++) {
		printf("%s ", a[k]->word);
		for(l=0;l<a[k]->frequency;l++) {
			printf("%d, ", a[k]->page[l]);
		}		
		printf("\n");
	}


	
}




int main(){
	int linenum, pagenum, i, wordnum=0, maxWordLength=0, flag=0, j;
	size_t len=0;
	char * sentence= NULL, *token;
	wordst *st[500];
	FILE *fp= fopen("labs/test.txt", "r");
	
	while(!feof(fp)){
		getline(&sentence, &len, fp);
		if(strtol(sentence, NULL, 0)!= 0){
			//printf("Is a page num\n");
			pagenum=atoi(sentence);
		}
		else{
			//printf("Is a line\n");
			token=strtok(sentence,DELIM); 
			while(token!= NULL && token!="\n"){
				for( i = 0; i<strlen(token); i++){
	  				token[i] = tolower(token[i]);
				}
				flag=0;
				for(j=0;j<wordnum;j++) {
					if(strcmp(st[j]->word, token)==0){
						flag=1;
						//printf("breaking, %s\n ", token);
						if(st[j]->page[(st[j]->frequency) - 1] != pagenum)
							st[j]->page[st[j]->frequency++]= pagenum;
						break;					
					}
				}

				if(flag == 0) {
					//printf("setting up word, %s\t ", token);
					st[wordnum]= (wordst*)malloc(sizeof(wordst));
					strcpy(st[wordnum]->word, token);
					st[wordnum]->page[st[wordnum]->frequency] = pagenum;
					st[wordnum]->frequency += 1;
					for( i = 0; i<strlen(st[wordnum]->word); i++){
  						st[wordnum]->code[i] = st[wordnum]->word[i] - 96; 
					}
					for( ;i<50; i++){
  						st[wordnum]->code[i] = 0; 
					}
					if(strlen(token)>maxWordLength){
						maxWordLength= strlen(token);
					}
					//st[wordnum]->page[st[wordnum]->frequency++]= pagenum;
					//printf("%x\n", st[wordnum]);
					wordnum++;
				}

				token= strtok(NULL,DELIM);
						
			}		 
		}
	//printf("%s\n", sentence);
	}

	// all the sorting goes in here
	radixSort(st, wordnum, maxWordLength);


}