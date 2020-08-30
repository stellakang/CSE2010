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
//void DeleteGraph(Graph G);
//void Topsort(Graph G);
//Queue MakeNewQueue(int X);
//int IsEmpty(Queue Q);
//int IsFull(Queue Q);
//int Dequeue(Queue* Q);
//void Enqueue(Queue* Q, int X);
//void DeleteQueue(Queue Q);
//void MakeEmpty(Queue Q);

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
	for(i=0;i<G->size;i++)
		printf(" %d",G->node[i]);
	printf("\n");	
	for(i=0;i<G->size;i++)
	{
		printf("%d ",G->node[i]);
		for(j=0;j<G->size;j++)
		{
			printf("%d ",G->matrix[i][j]);
		}
		printf("\n");
	}
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
	temp->matrix=(int**)malloc(sizeof(int)*temp->size+1);
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
	return G;
}

