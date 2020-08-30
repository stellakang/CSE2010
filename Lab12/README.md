1. BFS
 넓이 우선 탐색(breadth first search)의 줄임말이다. 시작 정점을 방문한 후 시작 정점에 인접한 모든 정점들을 우선 방문하는 방법. 더 이상 방문하지 않은 정점이 없을 때까지 방문하지 않은 모든 정점들에 대해서도 넓이 우선 검색을 적용한다.

2. DFS
 깊이 우선 탐색(depth first search)의 줄임말이다. 자료의 검색, 트리나 그래프를 탐색하는 방법이다. 한 노드를 시작으로 인접한 다른 노드를 재귀적으로 끝까지 탐색하면 다시 위로 와서 다음을 탐색하여 검색한다.

3. 코드 설명

메인함수와 각 함수 코드에 대한 설명을 덧붙였다.

-구조체-

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


-각 함수 목록-

1. stack* create_stack(int num)
{
	stack* temp=malloc(sizeof(stack));
	temp->top=-1;
	temp->max_stack_size=num;
	temp->content=malloc(sizeof(int)*num);
	return temp;
}
stack을 할당하고 top, max_stack_size 초기화해주고 content를 매개변수로 받은 num크기 만큼 할당해준다. 

2. void push(stack* s,int value)
{
	if(s->top<s->max_stack_size-1)
		s->content[++s->top]=value;
	else
		printf("Error: stack is full\n");
}
stack에서 value값을 집어넣는 함수이다. stack이 차있지 않으면 top값을 1증가시켜서 value값을 넣어준다.

3. int pop(stack* s)
{
	if(s->top>=0)
		return s->content[s->top--];
	else
	{
		printf("Error: stack is empty\n");
		return -1;
	}
}
비어있지 않으면 top을 인덱스로 갖는 원소를 반환하고 top값을 1감소시킨다.

4. void close_stack(stack* s)
{
	free (s->content);
	free(s);
}
마지막에 stack의 content를 free해주고 stack전체를 free해주는 함수이다.

5. queue* create_queue(int size)
{
	queue* temp=malloc(sizeof(queue));
	temp->content=malloc(sizeof(int)*size);
	temp->qsize=0;
	temp->max_queue_size=size;
	temp->first=0;
	temp->rear=-1;
	return temp;
}
queue를 형성하는 함수이다. 먼저 queue크기만큼을 임시 변수에 할당해주고 그 안의 content를 size만큼 할당해주고 나머지 변수를 초기화해준다.

6. void enqueue(queue* q,int value)
{
	if(IsFull(q))
		printf("Full queue");
	else{
		q->qsize++;
		q->rear=(q->rear+1)%q->max_queue_size;
		q->content[q->rear]=value;
	}
}
 queue에 원소를 넣는 과정이다. 차있지 않으면 원소를 넣고 size를 1증가시킨다. circularqueue이므로 rear값을 1증가시킨 값을 max_queue_size로 나눈 나머지로 변화시켜준다.

7. int dequeue(queue* q)
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
queue에서 제일 앞의 원소를 빼준다. 비어있지 않은 경우 시행하며 circular Queue를 고려하여 인덱스를 하나 증가시켜주고 전체 크기로 나눈 나머지를 first에 넣어준다. first에 저장했던 값을 반환시켜준다.

8. void close_queue(queue* q)
{
	free(q->content);
	free(q);
}
마지막에 queue의 content를 free시켜주고 전체 q를 free시켜주면 된다.

9. graph makeGraph(FILE* fi)
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
 먼저 g를 만들어주고 g의 weight를 할당해준다. 이차원 배열이기 때문에 두 번의 과정을 거친다. 이후, check_visit배열도 할당해주고 파일입출력 형식으로 받기 때문에 그 형식에 맞게 두 노드가 연결된 경우 weight배열을 1로 바꿔준다.

10. void DFS_recursive(graph g,int start,int end)
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
재귀적인 DFS 코드이다. 처음에 start를 출력해주고 visit배열을 1로 만들어준다. 그리고 그 노드와 연결되어있는 노드에 대해서 visit배열이 0인 경우, 즉 방문 안 한 노드의 경우 재귀적으로 함수를 호출하여 탐색하도록 한다. 만약 end노드를 탐색한 경우에는 다른 노드를 탐색할 필요가 없으므로 break를 해준다. 

11. void DFS_iterative(graph g,int start, int end)
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
stack을 이용하여 stack이 비어있지 않을 때까지 제일 위에 있는 원소를 pop하고 그 원소가 방문하지 않은 노드라면 출력해준다. 만약 이 노드가 end노드라면 break해주고 아니라면 연결되어있는 다른 노드들을 stack에 넣어준다. 그리고 이 노드의 visit배열을 1로 바꿔준다. 

12. void BFS_search(graph g,int start,int end)
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
queue가 비어있지 않을 때까지 queue의 제일 앞 원소를 출력하고 이 노드가 end노드라면 break해준다. end노드가 아니면 연결되어있는 다른 노드에 대해서 visit하지 않은 노드이면 visit배열을 1로 바꿔주고 queue에 넣어준다. 

13. int IsEmpty(queue* q)
{
	return q->qsize==0;
}
queue가 비어있는지 확인하는 함수이다.

14. int IsFull(queue* q)
{
	return q->qsize==q->max_queue_size;
}
queue가 다 차있는지 확인하는 함수이다.

15. main 함수
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
파일 입출력 형식을 따르며 DFS(recursive), DFS(iterative), BFS 순서대로 출력한다. 이때, 중간 중간에서는 check배열을 모두 0으로 초기화한 후, 탐색을 시작해야한다. 그리고 마지막으로 메모리를 해제해 준다.