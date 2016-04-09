#include <stdio.h>
#include <stdlib.h>
//allocating memory to nodes;
int arr[100];
int q=0,count=0;

struct BST{
	int v1;
	int v2;
	int v3;
	int v4;
	struct BST* l;
	struct BST* r;
	struct BST* p;
};
typedef struct BST bst;

//bst* maxPriorNode;

void getInp(){
	int j=0;
	int q;
	while(scanf("%d", &q)>0){
		arr[j]=q;
		j++;
	}
	count=j/4;
}

bst* createNode(){
	bst* temp= malloc(sizeof(bst));
	temp->v1=-1;
	temp->v2=-1;
	temp->v3=-1;
	temp->v4=-1;
	temp->l=NULL;
	temp->r=NULL;
	temp->p=NULL;
	return temp;
}

/*int getKey(bst* node){
	int a;
	a=(1000*node->v1)+(100*node->v2)+(10*node->v3)+(1*node->v4);
	return a;
}
*/

void treeInsert(bst* root, bst* node){
	bst* a;
	bst* b;
	a=root;
	b=NULL;
	if(root==NULL){
		root->v1=node->v1;
		root->v2=node->v2;
		root->v3=node->v3;
		root->v4=node->v4;
	}
	else{
		//int x1=getKey(root);
		int kn=node->v4;
		while(a!=NULL){
			if(kn<a->v4){
				b=a;
				a=b->l;
			}
			else{
				b=a;
				a=b->r;
			}
		}
		node->p=b;
		if(kn<b->v4)	
			b->l=node;
		else
			b->r=node;
	}
}

/*
void getMaxPrior(bst* root, int max){
	//int max=root->v4;
	bst* x=root;
	bst* y=root->l;
	bst* z=root->r;
	while(x!=NULL){
		if(max<y->v4 && y!=NULL){
			max=y->v4;
			maxPriorNode=y;
		}
		else if(max<z->v4 && z!=NULL){
			max=z->v4;
			maxPriorNode=z;
		}
		else{
			//max=x->v4;
			maxPriorNode=x;
		}

		getMaxPrior(y, max);
		getMaxPrior(z, max);
	}
}
*/

bst* tree_min(bst* node){
	while(node->l!=NULL){
		node=node->l;
	}
	return node;
}

bst* tree_max(bst* node){
    while(node->r!=NULL)
        node=node->r;
    return node;
}


void transplant(bst* root, bst* u, bst* v){
	if(u->p==NULL){
		root=v;
	}
	else{
		if(u==(u->p)->l){
			(u->p)->l=v;
		}
		else{
			(u->p)->r=v;
		}
	}
	if(v!=NULL){
		v->p=u->p;
	}
}

void treeDelete(bst* root, bst* z){
	if(z->l==NULL){
		transplant(root, z, z->r);
	}
	else{
		if(z->r==NULL){
			transplant(root, z, z->l);
		}
		else{
			bst* y= tree_min(z->r);
			if(y->p!=z){
				transplant(root,y,y->r);
				y->r=z->r;
				(y->r)->p=y;
			}
			transplant(root,z,y);
			y->l=z->l;
			(y->l)->p=y;
		}
	}
}

int main(void){
    bst* root=createNode();
    int a=0,time=0;
    bst* maxPriorNode=NULL;
    
    //T=0
    getInp();
    while(count>0){
        if(arr[a+1]==time){
            if(root->v1==-1){
                root->v1=arr[a];
                root->v2=arr[a+1];
                root->v3=arr[a+2];
                root->v4=arr[a+3];
                count--;
                a=a+4;
                }
            while(arr[a+1]==time){
                bst* temp=createNode();
                temp->v1=arr[a];
                temp->v2=arr[a+1];
                temp->v3=arr[a+2];
                temp->v4=arr[a+3];
                treeInsert(root, temp);
                count--;   
                a=a+4;
            } 
            if(maxPriorNode==NULL){
                maxPriorNode=tree_max(root);
                treeDelete(root, maxPriorNode);
                printf("%d", maxPriorNode->v1);
            }
            else{
                if(maxPriorNode->v4<tree_max(root)->v4){
                    treeInsert(root,maxPriorNode);
                    maxPriorNode=tree_max(root);
                    treeDelete(root, maxPriorNode);
                    printf("%d", maxPriorNode->v1);
                }
                
                
            }
        }
    
        else{
            printf("0\n");
        }   
        
        
        time++;
        if(maxPriorNode!=NULL){
        	maxPriorNode->v3--;	
        }
    }
    
    while(root!=NULL){
    	maxPriorNode=tree_max(root);
    	while(maxPriorNode->v3>0){
    		printf("%d",maxPriorNode->v1);
    		maxPriorNode--;
    	}
    	treeDelete(root,maxPriorNode);
    }    
return 0;   
}