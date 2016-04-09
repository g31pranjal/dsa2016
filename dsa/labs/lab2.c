#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct st {   
	char q[1000];
	int nt;
} st;

int empty(st *s) {
	if(s->nt == -1)
		return 1;
	else
		return 0;
}

void push(st *s,char x) {
	s->nt = s->nt + 1;
	s->q[s->nt] = x;
}

char pop(st *s) {
	char temp;
	temp = s->q[s->nt];
	s->nt = s->nt -1;
	return temp;
}

void pre(st *s) {
	s->nt=-1;
}

int prio(char z,char q) {
	if(z=='('||q=='(')
		return 0;
	else if(z==')')
		return 1;
	else {
		if(z=='/'||z=='*')
			return 1;
		else if(z=='+'||z=='-'){
			if(q=='/'||q=='*')
				return 0;
			else
				return 1;
		}
	}
}

char top (st *s) {
	char x=s->q[s->nt];
	return x;
}

int main() {    
	int i,j,k=0,l,r;
	char a[1000],b[1000],x,n,m;
	gets(a);

	st s,v;
	pre(&s);

	l = strlen(a);
	
	for(i=0;i<l;i++) {
		if((a[i]>=65&&a[i]<=90)||(a[i]>=97&&a[i]<=122)) {
			b[k++]=a[i];
		}
		else {
			while(!empty(&s)&&prio(top(&s),a[i])) {   
				x = pop(&s);
				b[k++]=x;
			}
			if(empty(&s)||a[i]!=')') {
				push(&s,a[i]);
			}
			else {
				pop(&s);
			}
		}
	}

	while(!empty(&s)) {
		x=pop(&s);
		b[k++]=x;
	}

	
	b[k]='\0';
	puts(b);
	

	
	int temp = 1;
	i=0;

	for(i=0;i<k;i++) {

		if((b[i]>=65&&b[i]<=90)||(b[i]>=97&&b[i]<=122))
			push(&v,b[i]);
		else {
			
			n=pop(&v);
			m=pop(&v);

			if(m>=49&&m<57)
				printf("LD\tTEMP%c\n",m);
			else
				printf("LD\t%c\n",m);

			if(b[i]=='/')
				if(n>=49&&n<57)
					printf("DV\tTEMP%c\n",n);
				else
					printf("DV\t%c\n",n);       
			if(b[i]=='*')
				if(n>=49&&n<57)
					printf("ML\tTEMP%c\n",n);
				else
					printf("ML\t%c\n",n);
			if(b[i]=='-')
				if(n>=49&&n<57)
					printf("SB\tTEMP%c\n",n);
				else
					printf("SB\t%c\n",n);  
			if(b[i]=='+')
				if(n>=49&&n<57)
					printf("AD\tTEMP%c\n",n);
				else
					printf("AD\t%c\n",n);

			printf("ST\tTEMP%d\n",temp);
			push(&v, '0'+temp);
			
			temp = temp + 1;
			if(temp == 10)
				temp = 1;
		}
	}
	return 0;
}