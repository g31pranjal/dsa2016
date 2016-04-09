#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char str[100];
long long h;
struct node
{
    long long n1,n2,h1,h2,l1,l2,leaf;
    int value;
    struct node* next;
    struct node* left;
    struct node* right;
    struct node* third;
    struct node* parent;
    struct node* snode;
};
typedef struct node node;
typedef node* nodeptr;
nodeptr front=NULL;
nodeptr rear;
nodeptr root;
nodeptr top=NULL;
void add(nodeptr* rear,nodeptr xyz)
{   
    //printf("entered");
    nodeptr curr;
    curr=*rear;
    //printf("entered");
    if(curr==NULL)
        {
            front=xyz;
            //printf("still in");
            (*rear)=front;
            front->next=NULL;
        }
    else
    {
        //printf("still in");
        curr->next=xyz;
        *rear=xyz;
       
    }
    xyz->next=NULL;

    //printf("still in");
}
nodeptr remo(nodeptr* front)
{
    nodeptr temp=(nodeptr)malloc(sizeof(node));

    temp=(*front);
    if(temp->next==NULL)
        {rear=*front=NULL;
            }
    *front=temp->next;
   
    //printf("inside remove%d\n",front->data);
    return temp;
}
void push(nodeptr *alpha){
    if(top==NULL)
           {
               top=*alpha;
               top->snode=NULL;
           }
       else
       {
           (*alpha)->snode=top;
           top=*alpha;
       }
}
int emptyq(){
    if(front==NULL)return 1;
    else return 0;
}
int empty(){
    if(top==NULL)return 1;
    else return 0;
}

nodeptr pop(){
    if(top==NULL)exit(1);
    else{
        nodeptr del=(nodeptr)malloc(sizeof(struct node));
        del=top;
        top=top->snode;
        return del;
    }
}
void print()
{
    nodeptr temp=front;
    //printf("front data:%d\n",front->data);
    while(front->next!=NULL)
        {    printf("hello");
            printf("%dX%d\n",temp->n1,temp->n2);
            temp=temp->next;
        }
        printf("%dX%d\n",temp->n1,temp->n2);
        printf("\n");       
}

void final(nodeptr root)
{
    if(root==NULL)
        return;
    printf("%d",root->value);
    final(root->left);
    final(root->right);
}
int num_split(long long n,int use)
{
    long long num;
    num=n;
    //printf("n:%d",n);
    long long j=0,d=1,k;
    //printf("%d",j);
    for(k=0;k<use;k++)
        d=d*10;
    //printf("%d ",d);
    h=num/d;
    //printf("h:%d ",h);
    long long l=num %d;
    //printf("l:%d\n",l);
return l;
}
int numdig(long long n)
{
    int j=0,d=1,k;
    while(n>0)
    {
        n=n/10;
        j++;
    }
    return j;
}
void populate()
{   
    while(!emptyq())
    {
        nodeptr temp=(nodeptr)malloc(sizeof(node));
        temp=remo(&front);
        //printf("%d %d\n",temp->n1,temp->n2);
        //if((numdig(temp->n1)==1)&&(numdig(temp->n2)==1))
        if((temp->n1<10)&&(temp->n2<10))
        {
            push(&temp);
            temp->left=NULL;
            temp->right=NULL;
            temp->third=NULL;
            temp->leaf=1;
            continue;
        }
        long long big;
        
        if(temp->n1>=temp->n2)
            big=temp->n1;
        else big=temp->n2;
        int use=numdig(big);
        if(use%2==1)
            use=use+1;
        int num=use/2;
        //printf("%d ",use);
        temp->l1=num_split(temp->n1,num);
        temp->h1=h;
        temp->l2=num_split(temp->n2,num);
        temp->h2=h;
        nodeptr child1=(nodeptr)malloc(sizeof(node));
        nodeptr child2=(nodeptr)malloc(sizeof(node));
        nodeptr child3=(nodeptr)malloc(sizeof(node));
        child1->n1=temp->h1+temp->l1;
        child1->n2=temp->h2+temp->l2;
        child1->value=1;
        child1->parent=temp;
        //printf("%d %d\n",child1->n1,child1->n2);
        child2->n1=temp->h1;
        child2->n2=temp->h2;
        child2->value=2;
        //printf("%d %d\n",child2->n1,child2->n2);
        child3->n1=temp->l1;
        child3->n2=temp->l2;
        child3->value=3;
        //printf("%d %d\n",child3->n1,child3->n2);
        temp->left=child1;
        temp->right=child2;
        temp->third=child3;
        add(&rear,child1);
        add(&rear,child2);
        add(&rear,child3);
        //push(&temp);
        temp->leaf=0;
        //populate(child1);
        //populate(child2);
        //populate(child3);
    }
}
void printvalue(nodeptr final)
{

if(final->value==1)
        add(&rear,(final->parent));
    if(final->leaf==1)
    {
        long long total=final->n1*final->n2;
        printf("%lldX%lld=%lld",final->n1,final->n2,total);
    }
    else {
        int j=0,k;
        long long d=1,n;
        if(final->n1>final->n2)
            n=final->n1;
        else n=final->n2;
    /*while(n>0)
    {
        n=n/10;
        j++;
    }
    j=j/2;*/
    int use=numdig(n);
        if(use%2==1)
            use=use+1;
        int o=use/2;
    for(k=1;k<=o;k++)
        d=d*10;
    long long a=(final->left)->n1*(final->left)->n2;
    long long b=(final->right)->n1*(final->right)->n2;
    long long c=(final->third)->n1*(final->third)->n2;
    long long total=b*d*d+(a-b-c)*d+c;
    printf("%lldX%lld=",final->n1,final->n2);
    printf("%lldX%lldX%lld+(%lld-%lld-%lld)X%lld+%lld=%lld",b,d,d,a,b,c,d,c,total);
}
}
int main()
{
    int pos=10000000;
    root=(nodeptr)malloc(sizeof(node));
    scanf("%s",str);
    int l=strlen(str);
    long long i,num1=0,num2=0;
    for(i=0;i<l;i++)
    {
        if(str[i]=='X'||str[i]=='x')
            pos=i;
        if(i>pos)
        {
            num2=num2*10+(str[i]-'0');
        }
        else if(i<pos)
            num1=num1*10+(str[i]-'0');
    }
    root->n1=num1;
    root->n2=num2;
    root->next=NULL;
    add(&rear,root);   
    populate();
    /*while(!empty())
    {
        nodeptr temp=pop();
        printf("%d %d\n",temp->n1,temp->n2);
    }*/
    while(!empty())
    {
        nodeptr temp=pop();
        add(&rear,temp);
    }
    while(!emptyq())
    {
        printvalue(remo(&front));
        printf("\n");
    } 
    return 0;
}