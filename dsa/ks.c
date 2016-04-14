#include <stdio.h>
#include <math.h>

int q[10000];
int lev[10000];
int lab[10000]={0};
int xyz[10000],c=0,flag=0;

typedef struct node{
	int cst;
	int st;
	
}node;

node a[10000][10000];

void dfs(int t,int ind) {
	int j;
	for(j=0;j<=a[t][0].st;j++) {	
		if(ind==c&&j!=0) {
			if(lab[a[t][j].st]==1&&a[t][j].cst==xyz[ind]) {
				flag=1;
			}
		}
		else if(j!=0&&a[t][j].cst==xyz[ind]) {
			dfs(a[t][j].st,ind+1);
		}
	}
	return;
}


int main() {

	int n,x,y,i,q,coun,j,el,k,d=0,p,temp,r=0,tot=0;
	
	scanf("%d",&n);
	
	for(j=0;j<n;j++) {
		scanf("%d%d%d",&x,&lab[j],&coun);
		x=x-1;
		for(i=0;i<coun;i++) {
			scanf("%d%d",&el,&y);
			y=y-1;
			a[x][0].st++;
			a[x][a[x][0].st].st=y;
			a[x][a[x][0].st].cst=el;
		}
	}
	
	c=1;d=0;
	if(lab[0] == 1)
	{tot++;
	 printf("e\n");
	}
	for(k=1;k<50;k++)
	{	p=pow(2,k);
		d=0;r=0;
		while(p>0)
		{
		temp=c;
		d=r;
		while(1)
		{
			xyz[temp]=d%2;
			temp--;
			
			if(temp<0)
			break;
			d=d/2;
		}
		r++;
		p--;
			flag=0;
				dfs(0,1);
	if(flag==1)
		{	tot++;
	//printf("%d count ",c);
		
		for(i=1;i<=c;i++)
		{
			printf("%d",xyz[i]);
		}
		printf("\n");
			if(tot==10)
			return 0;
		}
		
		}
	
		c++;
	}
	
	return 0;
}