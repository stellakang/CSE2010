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
	int i,j;
	fscanf(fi,"%d-%d",&start,&end);

	printf("DFS recursive:");
	DFS_recursive(g,start,end);
	if(g.check_visit[end-1]==0)
		printf("cannot find");
	for(i=0;i<g.num;i++)
		g.check_visit[i]=0;

	printf("\nDFS iterative:");
	DFS_iterative(g,start,end);
	for(i=0;i<g.num;i++)
		g.check_visit[i]=0;

	printf("\nBFS:");
	BFS_search(g,start,end);
	printf("\n");
	
	for(i=0;i<g.num;i++)
		free(g.weight[i]);
	free(g.weight);
	free(g.check_visit);
	fclose(fi);
}

stack* create_stack(int num)
{
	stack* temp=malloc(sizeof(stack));
	temp->top=-1;
	temp->max_stack_size=num;
	temp->content=malloc(sizeof(int)*num);
	return temp;
}
void push(stack* s,int value)
{
	if(s->top<s->max_stack_size-1)
		s->content[++s->top]=value;
	else
		printf("Error: stack is full\n");
}
int pop(stack* s)
{
	if(s->top>=0)
		return s->content[s->top--];
	else
	{
		printf("Error: stack is empty\n");
		return -1;
	}
}
void close_stack(stack* s)
{
	free (s->content);
	free(s);
}
queue* create_queue(int size)
{
	queue* temp=malloc(sizeof(queue));
	temp->content=malloc(sizeof(int)*size);
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
	g.check_visit=malloc(sizeof(int)*500);
	for(i=0;i<500;i++)
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
	int i=1;
	int a=0;
		
	printf("%d ",start);
	g.check_visit[start-1]=1;	
	for(i=1;i<=g.num;i++)
	{
		if(g.weight[start][i]==1&&g.check_visit[i-1]==0)
		{
			DFS_recursive(g,i,end);
			if(g.check_visit[end-1]==1)
				break;
		}
	}
}
void DFS_iterative(graph g,int start, int end)
{
	stack* s=create_stack(g.num+1);
	push(s,start);
	int a;
	while(s->top>=0)
	{
		a=pop(s);
		int i;
		if(g.check_visit[a-1]==0)
		{
			printf("%d ",a);
			if(a==end)
				break;
			g.check_visit[a-1]=1;
			for(i=1;i<=g.num;i++)
			{
				if(g.weight[a][i]==1)
					push(s,i);
			}
		}
	}
	if(a!=end)
		printf("cannot find");
	close_stack(s);
}
void BFS_search(graph g,int start,int end)
{
	queue* q=create_queue(g.num+1);
	enqueue(q,start);
	g.check_visit[start-1]=1;
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
			if(g.weight[v][i]==1&&g.check_visit[i-1]==0)
			{
				g.check_visit[i-1]=1;
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

