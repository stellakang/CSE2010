#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node
{
	ElementType element;
	Position next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Insert(ElementType x, List L, Position P);
void Print(List L);

List head, p;
char inp;
int a, b;

int main(int argc, char* argv[]) {
	FILE *fp;
	fp=fopen(argv[1], "r");
	head = MakeEmpty(head);
	while (fscanf(fp, "%c", &inp) != EOF)
	{
		if (inp == 'i')
		{
			fscanf(fp, "%d %d", &a, &b);
			Insert(a, head, head);
		}
		else if (inp == 'p')
			Print(head);
	}
	fclose(fp);

	return 0;
}

List MakeEmpty(List L)
{
	L = (List)malloc(sizeof(struct Node));
	if (L == NULL)
	{
		printf("Out of Space\n");
		exit(-1);
	}
	L->element = 0;
	L->next = NULL;
	return L;
}
int IsEmpty(List L)
{
	return L->next == NULL;
}
int IsLast(Position P, List L)
{
	return P->next == NULL;
}
void Insert(ElementType x, List L, Position P)
{
	Position Tmp;
	Tmp = (Position)malloc(sizeof(struct Node));
	if (Tmp == NULL)printf("ERROR\n");
	Tmp->element = x;
	Tmp->next = P->next;
	P->next = Tmp;

}
void Print(List L)
{
	Position m = L;

	while (m->next != NULL)
	{
		printf("key:%d\t", m->next->element);
		m = m->next;
	}
	printf("\n");
}

