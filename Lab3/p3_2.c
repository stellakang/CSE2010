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
void Delete(ElementType x, List L);
Position FindPrevious(ElementType x, List L);
Position Find(ElementType x,List);
void DeleteList(List L);

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
			if(Find(a,head)!=NULL)
			{
				printf("ERROR\n");
			}
			else
			{
				if(b==-1)
					Insert(a, head, head);
				else
				{
					Position p=Find(b,head);
					if(p==NULL)
						printf("Insertion(%d) Failed : cannot find the location to be inserted\n",a);
					else
						Insert(a,head,p);
				}
			}
		}
		else if(inp=='d')
		{
			fscanf(fp,"%d",&a);
			Position p=Find(a,head);
			if(p==NULL)
				printf("Deletion failed : element %d is not in the list\n",a);
			else
				Delete(a,head);
		}
		else if(inp=='f')
		{
			fscanf(fp,"%d",&a);
			if(FindPrevious(a,head)==head)
				printf("Key of the previous nod of %d is header.\n",a);
			else if(Find(a,head)==NULL)
				printf("Could not find %d in the list\n",a);
			else
				printf("Key of the previous node of %d is %d.\n",a,FindPrevious(a,head)->element);
		}
		else if (inp == 'p')
			Print(head);
	}
	fclose(fp);
	DeleteList(head);

	return 0;
}

List MakeEmpty(List L)
{
	if (L != NULL) DeletList(L);
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
	if (Tmp == NULL)
	{
		printf("ERROR\n");
		exit(-1);
	}
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
void Delete(ElementType x, List L)
{
	Position P, Tmp;

	P=FindPrevious(x,L);
	if(!IsLast(P,L))
	{
		Tmp=P->next;
		P->next=Tmp->next;
		free(Tmp);
	}
}
Position Find(ElementType x, List L)
{
	Position P;
	P=L->next;
	while(P!=NULL&&P->element!=x)
		P=P->next;
	return P;
}
Position FindPrevious(ElementType x,List L)
{
	Position P;
	
	P=L;
	while(P->next!=NULL&&P->next->element!=x)
		P=P->next;
	return P;
}
void DeleteList(List L)
{
	Position P,Tmp;
	P=L->next;
	L->next=NULL;
	while(P!=NULL)
	{
		Tmp=P->next;
		free(P);
		P=Tmp;
	}
}




