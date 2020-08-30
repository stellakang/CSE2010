#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph{
	int num;
	int** weight;
	int* check_visit;
}graph;

typedef struct Stack{
	int* content;
	int top;
	int max_stack_size;
}stack;

typedef struct CircularQueue{
	int* content;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
}queue;

stack* create_stack(int num);
void push(stack* s,int value);
int pop(stack* s);
void close_stack(stack* s);
queue* create_queue(int size);
void enqueue(queue* q,int value);
int dequeue(queue* q);
void close_queue(queue* q);
graph makeGraph(FILE* fi);
void DFS_recursive(graph g,int start,int end);
void DFS_iterative(graph g,int start, int end);
void BFS_search(graph g,int start,int end);
int IsFull(queue* q);
int IsEmpty(queue* q);

void main(int argc, char* argv[])
{
	FILE *fi=fopen(argv[1],"r");
	graph g=makeGraph(fi);

	int start,end;
	fscanf(fi,"%d-%d",&start,&end);

	//printf("DFS recursive:");
	//DFS_recursive(g,start,end);
	//if(g.check_visit[end-1]==0)
	//	printf("cannot find");
	//reset g.check_visit

	//printf("\nDFS iterative:");
	//DFS_iterative(g,start,end);
	//reset g.check_visit

	printf("BFS:");
	BFS_search(g,start,end);
	printf("\n");
	int i,j;
	for(i=0;i<g.num;i++)
		free(g.weight[i]);
	free(g.weight);
	free(g.check_visit);
	fclose(fi);
}

/*stack* create_stack(int num)
{

}*/
void push(stack* s,int value)
{
}
/*int pop(stack* s)
{
}*/
void close_stack(stack* s)
{
}
queue* create_queue(int size)
{
	queue* temp=malloc(sizeof(queue));
	temp->content=malloc(sizeof(queue)*size);
	temp->qsize=0;
	temp->max_queue_size=size;
	temp->first=0;
	temp->rear=-1;
	return temp;
}
void enqueue(queue* q,int value)
{
	if(IsFull(q))
		printf("Full queue");
	else{
		q->qsize++;
		q->rear=(q->rear+1)%q->max_queue_size;
		q->content[q->rear]=value;
	}
}
int dequeue(queue* q)
{
	if(IsEmpty(q))
	{	
		printf("Empty queue");
	}
	else
	{
		int value=q->content[q->first];
		q->qsize--;
		q->first=(q->first+1)%q->max_queue_size;
		return value;
	}
}
void close_queue(queue* q)
{
	free(q->content);
	free(q);
}
graph makeGraph(FILE* fi)
{
	int i;
	graph g;
	fscanf(fi,"%d",&g.num);
	g.weight=malloc(sizeof(int*)*g.num+1);
	for(i=0;i<g.num+1;i++)
		g.weight[i]=malloc(sizeof(int)*g.num+1);
	g.check_visit=malloc(sizeof(int)*g.num+1);
	for(i=0;i<g.num+1;i++)
		g.check_visit[i]=0;
	char temp;
	while(temp!='\n')
	{
		int a,b;
		fscanf(fi,"%d-%d",&a,&b);
		g.weight[a][b]=1;
		temp=fgetc(fi);
	}

	return g;
}
void DFS_recursive(graph g,int start,int end)
{
}
void DFS_iterative(graph g,int start, int end)
{
}
void BFS_search(graph g,int start,int end)
{
	queue* q=create_queue(g.num+1);
	enqueue(q,start);
	g.check_visit[start]=1;
	int v;
	while(!IsEmpty(q))
	{
		v=dequeue(q);
		printf("%d ",v);
		if(v==end)
			break;

		int i;
		for(i=1;i<g.num+1;i++)
		{
			if(g.weight[v][i]==1&&g.check_visit[i]==0)
			{
				g.check_visit[i]=1;
				enqueue(q,i);
			}
		}
	}
	if(v!=end)
		printf("cannot find");
	close_queue(q);
}

int IsEmpty(queue* q)
{
	return q->qsize==0;
}
int IsFull(queue* q)
{
	return q->qsize==q->max_queue_size;
}

