#include <stdio.h>

struct node {
	int n1;
	int n2;
	int n;
	int nd;
};

struct node arr[20000];

int test=0;

int power(int n, int a) {
	int i,ans=1;
	for(i=0;i<a;i++)
	{
		ans=ans*n;
	}
	return ans;
}

int max(int a,int b)
{
	if(a>b)
		return a;
	else 
		return b;
}

int isleafnode(int i)
{
	if(arr[i].n1<10 || arr[i].n2<10)
		return 1;
	else 
		return 0;
}

int numdigits(int n)
{
	if(n<10)
		return 1;
	else
	{
		int c=0;
		while(n>0)
		{
			n=n/10;
			c++;
		}
		return c;
	}
}


int mul(int i,int n1,int n2)
{
	test++;
	arr[i].n1=n1;
	arr[i].n2=n2;
	if(isleafnode(i))
	{
		//printf("yes");
		arr[i].n=n1*n2;
		return arr[i].n;
	}
	else
	{
		int m1=numdigits(n1),m2=numdigits(n2);
		int m=max(m1,m2);
		
		arr[i].nd=m;			//number of digits in ith node
		
		int h1,h2,l1,l2;
		l1 = n1 % (power(10,m/2));
		l2 = n2 % (power(10,m/2));
		h1 = n1 / (power(10,m/2));
		h2 = n2 / (power(10,m/2));
	/*	
		arr[3*i+1].n1=(h1+l1);
		arr[3*i+1].n2=(h2+l2);
		arr[3*i+2].n1=(h1);
		arr[3*i+2].n2=(h2);
		arr[3*i+3].n1=(l1);;
		arr[3*i+3].n2=(l2);
	*/	
		int a=mul(3*i+1,h1+l1,h2+l2);
		int b=mul(3*i+2,h1,h2);
		int c=mul(3*i+3,l1,l2);
		
		arr[i].n = b*power(10,2*(m/2)) + (a-b-c)*power(10,m/2) + c;
		
		return arr[i].n;
	}
}


int main() {
	int x,y,i;
	char temp;
	
	scanf("%d %c %d",&x,&temp,&y);
	
	for(i=0;i<20000;i++)
		arr[i].n=-1;

	mul(0,x,y);
	
	//printf("%d\n",test);
	i=0;
	while(arr[i].n!=-1)
	{
		//printf("%d x %d = %d\n",arr[i].n1,arr[i].n2,arr[i].n);
		i++;
	}
	i--;
	
	for( ;i>=0;i--)
	{
		if(isleafnode(i))
		{
			printf("%dX%d=%d\n",arr[i].n1,arr[i].n2,arr[i].n);
		}
		else
		{
			int a=arr[3*i+1].n;
			int b=arr[3*i+2].n;
			int c=arr[3*i+3].n;
			int nd2=power(10,(arr[i].nd)/2);
			printf("%dX%d=%dX%dX%d+(%d-%d-%d)X%d+%d=%d\n",
							arr[i].n1,arr[i].n2,b,nd2,nd2,a,b,c,nd2,c,arr[i].n );
		}
	}
	
	//printf("%d %d",a,b);
	
	return 0;
}