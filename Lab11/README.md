1. Dijkstra
 가중치가 있는 그래프의 최단 경로를 구하는 알고리즘이다. 출발 정점에서 시작하여 현재의 정점까지의 값과 인접한 정점의 가중치 합이 가장 작은 정점을 다음 정점으로 선택하고 그 경로를 최단 경로에 포함시킨다. 이 과정을 모든 정점이 선택될 때까지 반복한다.


2. 코드 설명

메인함수와 각 함수 코드에 대한 설명을 덧붙였다.

-구조체-
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

-각 함수 목록-

Graph CreateGraph(int size);
void printShortestPath(Graph g);
Heap* createMinHeap(int heapSize);
void InsertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);
int IsEmpty(Heap* minHeap);
int IsFull(Heap* minHeap);

1. Graph CreateGraph(int size)
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
 구조체로 된 그래프를 형성하는 과정이다. 임시로 temp를 만들고 temp의 size를 size로 초기화한다. temp의 vertices는 2차원 배열을 만들어야 하므로 (int**)malloc(sizeof(int*)*temp.size);로 먼저 할당한 후에 각 행에 대해서도 for문을 이용하여 똑같이 할당해준다. 그리고 vertices의 모든 원소를 0으로 초기화해준 후에 temp를 반환한다.

2. void insertToMinHeap(Heap* minHeap, int vertex, int distance)
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
Heap에 넣고자하는 노드를 넣는 과정이다. 다익스트라의 경우 거리가 제일 작은 노드를 구해야하는 과정이 필요하므로 distance를 고려하여 힙에 넣는다. 물론 heap이 다 차있는 경우에는 넣을 수 없으며 힙이 다 차있지 않은 경우에 먼저 제일 끝에 있는 원소의 인덱스에서 하나 증가시킨 후에 자신에게 맞는 위치에 다다를 때까지 부모노드에 접근하여 크기를 비교하고 부모노드의 정보를 현재 노드에 저장한다. 그리고 맞는 위치에 도달하면 그 인덱스에 현재 노드의 번호와 거리를 저장한다.

3. void printShortestPath(Graph g)
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
 모든 nodes의 거리를 inf로 (미리 10000으로 정의했음.) 초기화하고 prev값도 0으로 초기화하고 vertex는 각 인덱스 번호와 일치하게 초기화한다. 그리고 시작점 노드인 1의 dist를 0으로 초기화하고 위에서 createMinHeap함수로 만들었던 pq힙에 넣는다. 그리고 힙이 비어있지 않을 때까지 다음 과정을 반복하는데 제일 거리가 작은 노드를 꺼내고 그 노드와 연결된 노드를 찾는다. 연결된 노드의 거리보다 현재 노드의 거리에서 연결된 노드까지의 weight를 더한 거리가 짧으면 dist를 바꿔주고 힙에 넣어주며 prev에 현 노드의 번호를 저장해준다.
마지막에는 출력을 해주기 위해 재귀적으로 prev노드를 호출하여 1부터의 경로를 출력하는 printResult함수를 호출하고 마지막으로 출력 형식에 맞게 cost를 출력해준다.   

4. Heap* createMinHeap(int heapSize)
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
 힙을 만드는 함수이다. 처음에 구조체 크기만큼 할당해주고 할당이 제대로 되었을 경우에는 Size값을 0으로 초기화하며 Capacity값을 heapSize-1로 초기화한다. (메인함수에서 매개변수로 size+1을 넘겨주었으므로 g.size는 실제값보다 1크다. 따라서 g.size를 넘겨받아으므로 heapSize-1로 저장할 수 있다. )

5. void printResult(Graph g,int i)
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
 경로를 출력하는 함수이다. 각 노드마다 prev에 전 노드를 저장했으므로 재귀적으로 함수를 호출하면 경로를 출력할 수 있다. 다만 1일 경우에 함수를 종료하면 된다.

6. int IsEmpty(Heap* minHeap)
{
	return minHeap->Size==0;
}
 힙이 비어있는지 확인하는 함수이다. 힙의 size가 0이면 1을 0이 아니면 0을 리턴한다.

7. int IsFull(Heap* minHeap)
{
	return minHeap->Capacity <= minHeap->Size;
}
 힙이 차있는지 확인하는 함수이다. 힙의 size가 Capacity와 같거나 크면 1을 리턴하고 아니면 0을 리턴한다.
 
8. Node deleteMin(Heap* minHeap)
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
 비어있지 않을 경우 delete가 가능하다. 인덱스1의 원소에 해당하는 노드를 저장하고 마지막 노드의 인덱스를 저장한다. 그리고 자식노드 중에 작은 dist값을 가지는 노드를 찾고 이 노드의 dist랑 마지막 노드의 dist를 비교하여 작은 노드를 현 노드에 저장한다. 만약 마지막 노드의 dist가 작으면 break하여 i의 인덱스에 저장한다. 그리고 제일 dist가 작은 값(미리 저장해던 값)을 반환한다. 

9. main 함수
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
파일 입출력 형식을 따르며 size에 1증가시킨 값으로 그래프를 만들고 입력형식에 맞게 입력을 받는다. 마지막으로 printShortestPath(g)를 호출한다.