#include <stdio.h>
#include <stdlib.h>

typedef struct Heap heap;

struct Heap {
	int hs;
	int * arr;
};

int parent(int i) {
	return (i-1)/2;
}

int left(int i) {
	return 2*i + 1;
}

int right(int i) {
	return 2*i + 2;
}

heap * initHeap() {
	heap * h = (heap *)malloc(sizeof(heap));
	h->arr = (int *)malloc(50*sizeof(int));
	return h;
}

void heapSwap(heap * h, int i, int j) {
	int t = h->arr[i];
	h->arr[i] = h->arr[j];
	h->arr[j] = t;
}
 
void minHeapify(heap * h, int i) {
	int l = left(i);
	int r = right(i);
	int min = i;

	if(l < h->hs && h->arr[l] < h->arr[min]) {
		min = l;
	}
	if(r < h->hs && h->arr[r] < h->arr[min]) {
		min = r;
	}

	if(min != i) {
		heapSwap(h, min, i);
		minHeapify(h, min);
	}
}

void buildMinHeap(heap * h) {
	int t = h->hs/2;
	int i;
	for(i=t;i>=0;i--) {
		minHeapify(h, i);
	}
}

int extractMin(heap * h) {
	int t = h->arr[0];
	h->arr[0] = h->arr[h->hs - 1];
	h->hs = h->hs - 1;
	minHeapify(h, 0);

	return t;
}

void heapDecreaseKey(heap * h, int i, int val) {
	if(h->arr[i] < val) {

	}
	else {
		h->arr[i] = val;
		while(i > 0 && h->arr[parent(i)] > h->arr[i]) {
			heapSwap(h, parent(i), i);
			i = parent(i);
		}
	}
}




int main() {

	heap * h = initHeap();

	h->arr[0] = 1;
	h->arr[1] = 6;
	h->arr[2] = 4;
	h->arr[3] = 3;
	h->arr[4] = 7;
	h->arr[5] = 2;
	h->arr[6] = 4;
	h->arr[7] = 9;
	h->arr[8] = 0;
	h->arr[9] = 3;

	h->hs = 10;

	buildMinHeap(h);

	int i;
	for(i=0;i<h->hs;i++) {
		printf("%d\n", h->arr[i]);
	}

}
