#include <stdio.h>
#include <stdlib.h>

typedef struct dyn entry;

struct dyn {
	int g1;
	int g2;
	int steps;
	entry * next;
};

entry * entries, *top, *rear;

int try = 1;


int addToQ(int sn1, int sn2, int steps) {
	int i=0;

	entry * pt = entries;

	while(pt != NULL) {
		if(pt->g1 == sn1 && pt->g2 == sn2) {
			return 0;	
		}
		pt = pt->next;
	}

	entry * node = (entry *)malloc(sizeof(entry));

	node->g1 = sn1;
	node->g2 = sn2;
	node->next = entries;
	entries = node;

	entry * node2 = (entry *)malloc(sizeof(entry));
	
	node2->g1 = sn1;
	node2->g2 = sn2;
	node2->steps = steps + 1;
	rear->next = node2;
	node2->next = NULL;
	rear = node2;

	if(top == NULL)
		top = node2;

	return 0;

}



int evalg(int l1, int l2, int tr) {

	int sn1, sn2, steps, dif, s1, s2;
	
	while(top != NULL) {
		s1 = top->g1;
		s2 = top->g2;
		steps = top->steps;
		top = top->next;

		printf("s1 : %d\t, s2 : %d\t, steps : %d \n", s1,s2, steps);

		if(s1 == tr || s2 == tr) {
			return steps;
		}

		if(s1 == 0) {	
			printf("TRY : %d\n", ++try);				// fill A completely
			sn1 = l1;
			sn2 = s2;
			addToQ(sn1, sn2, steps);

		}
		
		if(s2 == 0) {					// fill B completely
			printf("TRY : %d\n", ++try);				// fill A completely
			sn1 = s1;
			sn2 = l2;
			addToQ(sn1, sn2, steps);
		
		}
		
		if(s1 != 0) {					// empty A completely
			printf("TRY : %d\n", ++try);				// fill A completely
			sn1 = 0;
			sn2 = s2;
			addToQ(sn1, sn2, steps);

		}

		if(s2 != 0)	{					// empty B completely
			printf("TRY : %d\n", ++try);				// fill A completely
			sn1 = s1;
			sn2 = 0;
			addToQ(sn1, sn2, steps);

		}
		
		if(s1 != 0 && s2 != l2)	{		// a->b
			printf("TRY : %d\n", ++try);				// fill A completely
			dif = s1<(l2-s2)?s1:l2-s2;
			sn1 = s1 - dif;
			sn2 = s2 + dif;
			addToQ(sn1, sn2, steps);
		}

		if(s2 != 0 && s1 != l1)	{		// b->a
			printf("TRY : %d\n", ++try);				// fill A completely
			dif = s2<(l1-s1)?s2:l1-s1;
			sn1 = s1 + dif;
			sn2 = s2 - dif;
			addToQ(sn1, sn2, steps);
		}
	}
	if(top == NULL)
		return -1;
}

int main() {
	int tc = 0, i=0;
	scanf("%d", &tc);

	int g1[tc];
	int g2[tc];
	int tr[tc];

	for(i=0;i<tc;i++) {
		scanf("%d", &g1[i]);
		scanf("%d", &g2[i]);
		scanf("%d", &tr[i]);
	}

	for(i=0;i<tc;i++) {
		top = NULL;
		rear = NULL;
		entries = NULL;

		entry * node = (entry *)malloc(sizeof(entry));

		node->g1 = 0;
		node->g2 = 0;
		node->next = entries;
		entries = node;

		entry * node2 = (entry *)malloc(sizeof(entry));

		node2->g1 = 0;
		node2->g2 = 0;
		node2->steps = 0;
		node->next = rear;
		top = node2;
		rear = node2;

		printf("%d\n", evalg(g1[i], g2[i], tr[i]));
	}
	return 0;
}
