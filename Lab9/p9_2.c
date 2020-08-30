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
void Find(Heap *heap,int value);
int DeleteMax(Heap* heap);
void PrintHeap(Heap* heap);

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
		case 'd':
			DeleteMax(maxHeap);
			break;
		case 'p':
			PrintHeap(maxHeap);
			break;
		case 'f':
			fscanf(fi,"%d",&key);
			Find(maxHeap,key);
			break;
		}
	}
	free(maxHeap);	
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
	int check=0;
	if(IsFull(heap))
	{
		printf("Insertion Error : Max Heap is full.\n");
		return ;
	}
	for(i=1;i<=heap->Size;i++)
	{
		if(heap->Element[i]==value)
		{	
			check=1;
			break;
		}
	}
	if(check==0)
	{
		for(i=++heap->Size;heap->Element[i/2]<value&&i>=2;i/=2)
			heap->Element[i]=heap->Element[i/2];
		heap->Element[i]=value;
		//printf("insert %d\n",value);
	}
	else
		printf("%d is already in the heap.\n",value); 
	
}
int IsFull(Heap *heap)
{
	if(heap->Size==heap->Capacity)
		return 1;
	else
		return 0;
}
void Find(Heap *heap,int value)
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
	if(check==0)
		printf("%d is not in the tree.\n",value);
	else
		printf("%d is in the tree.\n",value);
}	
int DeleteMax(Heap* heap)
{
	int i,Child;
	int MaxElement, LastElement;

	if(heap->Size==0)
	{
		printf("Deletion Error : Max heap is empty!\n");
		return -1;
	}	

	MaxElement=heap->Element[1];
	LastElement=heap->Element[heap->Size--];	

	for(i=1;i*2<=heap->Size;i=Child)
	{
		Child=i*2;
		if(Child!=heap->Size&&heap->Element[Child+1]>heap->Element[Child])
			Child++;
		if(LastElement<heap->Element[Child])
			heap->Element[i]=heap->Element[Child];
		else
			break;
	}
	heap->Element[i]=LastElement;
	return MaxElement;
}
void PrintHeap(Heap* heap)
{
	int i;
	if(heap->Size==0)
		printf("Print Error : Max heap is empty!\n");
	else
	{
		for(i=1;i<=heap->Size;i++)
			printf("%d ",heap->Element[i]);
		printf("\n");
	}
}
