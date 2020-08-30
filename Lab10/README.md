1. Topological sort
Topological sort algorithm (위상정렬 알고리즘)이란 그래프 상의 정점들을 순서에 맞게 나열하는 것이다.
 이번 과제에서는 queue를 이용해서 구현하겠다.(queue나 stack을 이용해서 indegree가 0인 정점을 넣을 수 있다.)
 위상정렬의 대략적인 과정은 다음과 같다. 자세한 코드에 대한 설명은 2. 코드 설명에서 이어서 하겠다.

1. indegree가 0인 정점은 queue에 push한다.
2. indegree가 0인 정점과 이와 연결된 모든 간선을 지운다.
3. 남아있는 정점의 indegree를 갱신한다.
4. 그래프에 모든 정점이 없어질 때까지 이를 반복한다. 

A-B-C-D-E-F-G-H 순으로 위상정렬 가능. (queue에 넣는 순서에 따라 다양한 답이 나올 수 있다.)

2. 코드 설명

메인함수와 각 함수 코드에 대한 설명을 덧붙였다.

-구조체-
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

-각 함수 목록-

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

1. Graph CreateGraph(char* nodes);
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
 그래프를 리턴하기 위해 임시로 temp를 선언하고 할당한다. temp의 노드의 크기를 여유있게 500정도로 잡아 할당하고 nodes로 받은 문자열을 분리한다. while문을 이용해서 분리하는 코드를 구현하면 되는데 먼저, strtok(nodes, “ ”)로 처음 문자를 받고 atoi를 이용하여 integer로 변환한다. while문을 이용하여 tmp가 NULL이 아닐 때까지 반복한다. 이때, node에 각 값을 저장하고 temp안의 size를 하나씩 증가시켜준다.
 temp의 matrix를 할당해주고 (이차원 배열이므로 처음 할당해준 후, 각 행도 할당해주는 과정을 거친다.) matrix의 모든 자리를 0으로 초기화해준다.

2. Graph InsertEdge(int a,int b,Graph G);
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
 메인함수에서 분리해낸 a, b값을 그래프 G에 추가한다. node에서 a와 같은 값의 인덱스와, b와 같은 값의 인덱스를 각각 m,n에 저장한다. 그리고 matrix[m][n]을 1로 저장해준다. 방향이 있는 그래프이므로 edge의 방향이 가리키는 노드의 indegree를 하나 증가시켜준다. 즉, ind[n]을 하나 증가시켜준다. 그리고 Graph G를 반환해준다.
  
3. void DeleteGraph(Graph G);
 Graph의 matrix와 node를 free해준다. 이때, matrix는 이차원 배열이므로 각 행을 free해준 뒤에 전체 배열을 메모리 해제해준다. 
 
4. void Topsort(Graph G);
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
 Queue를 선언하고 MakeNewQueue를 호출하여 할당해준다. 그리고 맨 처음에 indegree가 0인 노드를 모두 Enqueue해준다.(표기하기 쉽도록 node배열의 인덱스를 Enqueue해주었다.) 그리고 Queue가 비어있지 않을 때까지 while문으로 과정을 반복해준다. 먼저 Queue에서 Dequeue를 해준 후에 그 값을 인덱스로 하는 node배열의 값을 출력해준다. 그리고 그 노드와 연결되어있는 다른 노드의 indegree를 하나씩 줄여준다. 이때, indegree가 0이면 Enqueue해준다. 

5. Queue MakeNewQueue(int X);
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
 Queue를 할당해주고 Queue의 key배열을 할당해준다. 초기화 과정을 거치는데 first값을 0, rear값을 –1로, qsize값을 0으로 초기화한다. 또한 max_queue_size를 X로 초기화하고 newQueue를 반환한다. 

6. int IsEmpty(Queue Q);
int IsEmpty(Queue Q)
{
	if(Q->qsize==0)
		return 1;
	else
		return 0;
}
 size가 0이면 비어있음을 의미하는 1을 0이 아니면 0을 반환한다. 

7. int IsFull(Queue Q);
int IsFull(Queue Q)
{
	if(Q->rear==Q->max_queue_size-1)
		return 1;
	else
		return 0;
}
 rear의 값과 max_queue_size-1이 같으면 차있음을 의미하는 1을 반환한다. 

8. int Dequeue(Queue Q);
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
 비어있지 않으면 제일 앞의 원소를 반환하며 first값을 1증가시키고 Queue의 size를 1감소시켰다. 

9. void Enqueue(Queue Q, int X);
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
 새로운 원소 X를 Queue에 넣는 함수이다. 차있지 않으면 rear값을 1증가시켜서 원소 X를 key[Q->rear]에 저장하고 qsize의 값도 1증가시킨다.
 
10. void DeleteQueue(Queue Q);
 Queue의 key배열을 free시켜준다.

11. void MakeEmpty(Queue Q);
 Queue가 빌 때까지 Dequeue함수를 호출한다. 

12. main 함수
 파일 입출력 형식을 따르며 한 줄로 값을 입력받고 CreateGraph함수를 호출한다. 그리고 fscanf로 문자열을 입력받고 CreateGraph에서 취했던 방식과 비슷하게 문자열을 분리시킨다. -를 기준으로 분리시키고 \0을 기준으로 분리시켜서 두 개의 문자열을 integer로 바꾼 후에 InsertEdge 함수를 호출하여 그래프의 간선을 추가한다. 그리고 DeleteGraph 함수를 호출하여 그래프를 지워준다.
