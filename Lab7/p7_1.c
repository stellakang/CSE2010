#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct{
	int Capacity;
	int Size;
	int *Element;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap* heap,int value);
int IsFull(Heap *heap);
int Find(Heap *heap,int value);

void main(int argc, char* argv[])
{
	FILE *fi=fopen(argv[1],"r");
	char cv;
	Heap* maxHeap;
	int heapSize, key;
	while(!feof(fi))
	{
		fscanf(fi,"%c",&cv);
		switch(cv){
		case 'n':
			fscanf(fi,"%d",&heapSize);
			maxHeap=CreateHeap(heapSize);
			break;
		case 'i':
			fscanf(fi,"%d",&key);
			Insert(maxHeap,key);
			break;
		}
	}
	
	fclose(fi);
}

Heap* CreateHeap(int heapSize){
	Heap *Tmp;
	Tmp=malloc(sizeof(struct HeapStruct));
	if(Tmp==NULL)
	{
		printf("Out of space!\n");
		exit(-1);
	}
	Tmp->Element=malloc(sizeof(int)*(heapSize+1));
	if(Tmp->Element==NULL)
	{
		printf("Out of space!\n");
		exit(-1);
	}
	
	Tmp->Size=0;
	Tmp->Capacity=heapSize;
	Tmp->Element[0]=0;
	return Tmp;
}

void Insert(Heap* heap,int value){
	int i;
	if(IsFull(heap))
	{
		printf("Priority queue is full\n");
		return ;
	}
	if(Find(heap,value)==0)
	{
		for(i=++heap->Size;heap->Element[i/2]<value&&i>=2;i/=2)
			heap->Element[i]=heap->Element[i/2];
		heap->Element[i]=value;
		printf("insert %d\n",value);
	}
	else
		printf("Insertion Error : There is already %d in the tree.\n",value); 
	
}
int IsFull(Heap *heap)
{
	if(heap->Size==heap->Capacity)
		return 1;
	else
		return 0;
}
int Find(Heap *heap,int value)
{
	int i;
	int check=0;
	for(i=1;i<=heap->Size;i++)
	{
		if(heap->Element[i]==value)
		{	
			check=1;
			break;
		}
	}
	return check;
}	
