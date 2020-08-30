#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue
{
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

struct _Graph
{
	int size;
	int* node;
	int** matrix;
};

Graph CreateGraph(char* nodes);
Graph InsertEdge(int a,int b,Graph G);
void DeleteGraph(Graph G);
void Topsort(Graph G);
Queue MakeNewQueue(int X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
int Dequeue(Queue Q);
void Enqueue(Queue Q, int X);
void DeleteQueue(Queue Q);
void MakeEmpty(Queue Q);

int ind[500];

int main(int argc, char *argv[])
{
	FILE *fi=fopen(argv[1],"r");
	char* num = (char*)malloc(sizeof(char)*500);
	char* string = (char*)malloc(sizeof(char)*500);
	int i,j; 
	Graph G;
	fgets(num,500,fi);
	G=CreateGraph(num);
	char* save=NULL;
	int c,d;
	while(fscanf(fi,"%s",string)!=EOF)
	{
		save=strtok(string,"-");
		c=atoi(save);
		save=strtok(NULL,"\0");
		d=atoi(save);
		G=InsertEdge(c,d,G);
	}
	Topsort(G);
	DeleteGraph(G);
	fclose(fi);
	return 0;
}
Graph CreateGraph(char* nodes)
{
	int i;
	Graph temp=malloc(sizeof(struct _Graph));
	temp->size=0;
	temp->node=malloc(sizeof(int)*500);
	char* tmp=strtok(nodes, " ");
	while(tmp!=NULL){
		int a=atoi(tmp);
		temp->node[temp->size]=a;
		temp->size++;
		tmp=strtok(NULL," ");		
	}	
	temp->matrix=(int**)malloc(sizeof(int*)*temp->size);
	for(i=0;i<temp->size;i++)
	{
		temp->matrix[i]=(int*)malloc(sizeof(int)*temp->size);
	}
	int a=0,b=0;
	for(a=0;a<temp->size;a++){
		for(b=0;b<temp->size;b++){
			temp->matrix[a][b] = 0;
		}
	}
	return temp;
}
Graph InsertEdge(int a, int b,Graph G)
{
	int i;
	int m,n;
	for(i=0;i<G->size;i++)
	{
		if(G->node[i]==a)
			m=i;
		if(G->node[i]==b)
			n=i;
	}
	G->matrix[m][n]=1;
	ind[n]++;
	return G;
}
void DeleteGraph(Graph G)
{	
	int i;
	for(i=0;i<G->size;i++)
	{
		free(G->matrix[i]);
	}
	free(G->matrix);
	free(G->node);
}
void Topsort(Graph G)
{
	int i;
	Queue Q=MakeNewQueue(G->size+1);
	for(i=0;i<G->size;i++)
	{
		if(ind[i]==0)
			Enqueue(Q,i);
	}
	while(!IsEmpty(Q))
	{
		int a=Dequeue(Q);
		printf("%d ",G->node[a]);
		for(i=0;i<G->size;i++)
		{
			if(G->matrix[a][i]==1)
			{
				ind[i]--;
				if(ind[i]==0)
					Enqueue(Q,i);
			}
		}
	}
	printf("\n");	
	DeleteQueue(Q);
}
Queue MakeNewQueue(int X)
{
	Queue newQueue=(Queue)malloc(sizeof(struct _Queue));
	newQueue->key=(int*)malloc(sizeof(int)*X);
	newQueue->first=0;
	newQueue->rear=-1;
	newQueue->qsize=0;
	newQueue->max_queue_size=X;
	return newQueue;
}
int IsEmpty(Queue Q)
{
	if(Q->qsize==0)
		return 1;
	else
		return 0;
}
int IsFull(Queue Q)
{
	if(Q->rear==Q->max_queue_size-1)
		return 1;
	else
		return 0;
}
int Dequeue(Queue Q)
{
	if(IsEmpty(Q))
		printf("Error!\n");
	else
	{
		int a=Q->key[Q->first];
		Q->first++;
		Q->qsize--;
		return a;
	}
}
void Enqueue(Queue Q, int X)
{
	if(IsFull(Q))
		printf("Error!\n");
	else
	{
		Q->qsize++;
		Q->rear++;
		Q->key[Q->rear]=X;		
	}
}
void DeleteQueue(Queue Q)
{
	free(Q->key);
}
void MakeEmpty(Queue Q)
{
	while(!IsEmpty(Q))
		Dequeue(Q);
}

