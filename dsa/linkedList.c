#include <stdio.h>
#include <stdlib.h>

typedef struct node n;

struct node {
	char data;
	n *link;
};

int isEmpty(struct node *top) {
	if(top == 0) {
		return 1;
	}
	else 
		return 0;
}


int front_push(struct node **top, char data) {
	struct node *nw = (struct node *)malloc(1*sizeof(struct node));
	nw->data = data;
	nw->link = NULL;
	if(isEmpty(*top)) {
		*top = nw;
		printf("%x\n", (*top));
	}
	else {
		nw->link = *top;
		*top = nw;
	}
	return 0;
}


char front_pop(struct node **top) {
	char tmp;
	if(isEmpty(*top)) {
		printf("nothing to pop out !");
		return 1;
	}
	else {
		tmp = (*top)->data;
		*top = (*top)->link;
		return tmp;
	}
}

int parse(struct node **top) {
	struct node *c_node = *top;
	while(c_node != NULL) {
		printf("%c -> ", c_node->data);
		c_node = c_node->link;
	}
	printf("\n");
}

int back_push(struct node **top, char data) {
	struct node *nw = (struct node *)malloc(1*sizeof(struct node));
	nw->data = data;
	nw->link = NULL;
	
	struct node *c_node = *top;
	while(1) {
		if(c_node->link == NULL) {
			break;
		}
		else
			c_node = c_node->link;
	}

	c_node->link = nw;

}

int main() {
	struct node *top = NULL;

	char a;
	
	char data;

	do {
		printf("enter the choice : \n");
		scanf("%c", &a);
		switch(a) {

			// push from front
			case '1' : 
				printf("Enter data : \n");
				scanf("\n%c", &data);
				front_push(&top, data);
				printf("---------------- successfully front pushed %c\n", data);
				break;

			// pop out from front
			case '2' : 
				scanf("%c", &data);
				data = front_pop(&top);
				printf("---------------- successfully front poped %d\n", data);
				break;

			// parse
			case '3' : 
				parse(&top);
				break;

			// push from back
			case '4' : 
				printf("Enter data : \n");
				scanf("\n%c", &data);
				back_push(&top, data);
				printf("---------------- successfully back pushed %c\n", data);
				break;


		}

	} while(a != '.');


}