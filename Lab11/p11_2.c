#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define inf 10000

typedef struct Node{
	int vertex;
	int dist;
	int prev;
}Node;
typedef struct Graph{
	int size;
	int** vertices;
	Node* nodes;
}Graph;
typedef struct Heap{
	int Capacity;
	int Size;
	Node* Element;
}Heap;
Graph CreateGraph(int size);
void printShortestPath(Graph g);
Heap* createMinHeap(int heapSize);
void InsertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);
int IsEmpty(Heap* minHeap);
int IsFull(Heap* minHeap);
void main(int argc, char* argv[])
{
	FILE *fi=fopen(argv[1], "r");
	Graph g;

	int size;
	fscanf(fi, "%d\n",&size);
	g=CreateGraph(size+1);
	char temp=0;
	while(temp!='\n')
	{
		int node1, node2, weight;
		fscanf(fi,"%d-%d-%d",&node1, &node2, &weight);
		g.vertices[node1][node2]=weight;
		temp=fgetc(fi);
	}
	printShortestPath(g);
	fclose(fi);
}

Graph CreateGraph(int size)
{
	int i,j;
	Graph temp;
	temp.size=size;
	temp.vertices=(int**)malloc(sizeof(int*)*temp.size);
	for(i=0;i<temp.size;i++)
	{
		temp.vertices[i]=(int*)malloc(sizeof(int)*temp.size);
	}
	temp.nodes=(Node*)malloc(sizeof(struct Node)*temp.size);
	for(i=0;i<temp.size;i++)
		for(j=0;j<temp.size;j++)
			temp.vertices[i][j]=0;
	return temp;		
}
void insertToMinHeap(Heap* minHeap, int vertex, int distance)
{
	int i;
	if(IsFull(minHeap))
	{
		printf("Error : Priority queue is full");
		return;
	}

	for(i=++minHeap->Size;i!=1&&minHeap->Element[i/2].dist>distance;i/=2)
		minHeap->Element[i].dist=minHeap->Element[i/2].dist;
	minHeap->Element[i].dist=distance;
	minHeap->Element[i].vertex=vertex;
}
void printResult(Graph g,int i)
{
	if(g.nodes[i].vertex==1)
	{	
		printf("1");
		return;
	}
	else
	{
		printResult(g,g.nodes[i].prev);
		printf("->%d",g.nodes[i].vertex);
	}
}

void printShortestPath(Graph g)
{
	int P,Q;
	int i;
	Heap* pq=createMinHeap(g.size);
	for(i=0;i<g.size;i++)
	{
		g.nodes[i].dist=inf;
		g.nodes[i].prev=0;
		g.nodes[i].vertex=i;
	}
	g.nodes[1].dist=0;
	insertToMinHeap(pq,g.nodes[1].vertex,g.nodes[1].dist);
	while(IsEmpty(pq)!=1)
	{
		Node n=deleteMin(pq);
		for(i=1;i<g.size;i++)
		{
			if(g.vertices[n.vertex][i]!=0)
			{
				int toGo=i;
				int toDis=n.dist+g.vertices[n.vertex][i];
				if(g.nodes[toGo].dist>toDis)
				{
					g.nodes[toGo].dist=toDis;
					insertToMinHeap(pq,toGo,toDis);
					g.nodes[toGo].prev=n.vertex;
				}
			}
		}
	}
	for(i=2;i<g.size;i++)
	{
		printResult(g,i);
		printf(" (cost : %d)\n",g.nodes[i].dist);		
	}
}

Heap* createMinHeap(int heapSize)
{
	Heap* H=(Heap*)malloc(sizeof(struct Heap));
	
	if(H==NULL){
		printf("Error : Out of Space.\n");
		return 0;
	}
	H->Size=0;
	H->Capacity=heapSize-1;
	H->Element=(Node*)malloc(sizeof(struct Node)*heapSize);

	return H;
}
int IsEmpty(Heap* minHeap)
{
	return minHeap->Size==0;
}
int IsFull(Heap* minHeap)
{
	return minHeap->Capacity <= minHeap->Size;
}

Node deleteMin(Heap* minHeap)
{
	if(IsEmpty(minHeap))
	{
		printf("Error : Priority queue is empty\n");
		return;
	}
	else
	{
		int i,child;
		Node MinElement=minHeap->Element[1];
		Node LastElement=minHeap->Element[minHeap->Size--];
		for(i=1;2*i<=minHeap->Size;i=child)
		{
			child=i*2;
			if(child!=minHeap->Size&&minHeap->Element[child].dist>minHeap->Element[child+1].dist){
				child++;
			}
			if(minHeap->Element[child].dist<LastElement.dist){
				minHeap->Element[i]=minHeap->Element[child];
			}
			else break;
		}
		minHeap->Element[i]=LastElement;
		return MinElement;	
	}
}

