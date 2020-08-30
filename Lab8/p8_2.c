#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode{
	ElementType Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

int Max(int num1,int num2);
int Height(Position P);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
AVLTree Insert(ElementType X, AVLTree T);
void PrintInorder(AVLTree T);
void DeleteTree(AVLTree T);

void main(int argc,char* argv[]){

	FILE *fp=fopen(argv[1],"r");
	AVLTree myTree=NULL;
	int element;
	
	while(fscanf(fp,"%d",&element)!=EOF){
		myTree=Insert(element,myTree);
		PrintInorder(myTree);
		printf("\n");
	}
	DeleteTree(myTree);
	fclose(fp);
}

Position SingleRotateWithLeft(Position node)
{
	Position TmpCell;

	TmpCell=node->Left;
	node->Left=TmpCell->Right;
	TmpCell->Right=node;

	node->Height=Max(Height(node->Left),Height(node->Right))+1;
	TmpCell->Height=Max(Height(TmpCell->Left),node->Height)+1;

	return TmpCell;
}
Position SingleRotateWithRight(Position node)
{
	Position TmpCell;

	TmpCell=node->Right;
	node->Right=TmpCell->Left;
	TmpCell->Left=node;

	node->Height=Max(Height(node->Left),Height(node->Right))+1;
	TmpCell->Height=Max(Height(TmpCell->Left),node->Height)+1;

	return TmpCell;
}
Position DoubleRotateWithLeft(Position node)
{
	node->Left=SingleRotateWithRight(node->Left);

	return SingleRotateWithLeft(node);
}
Position DoubleRotateWithRight(Position node)
{
	node->Right=SingleRotateWithLeft(node->Right);

	return SingleRotateWithRight(node);
}
AVLTree Insert(ElementType X, AVLTree T)
{
	if(T==NULL){
		T=malloc(sizeof(struct AVLNode));
		if(T==NULL)
		{	
			printf("Out of space!\n");
			exit(-1);
		}
		else{
			T->Element=X;
			T->Height=0;
			T->Left=T->Right=NULL;
		}
	}else if(X<T->Element){
		T->Left=Insert(X,T->Left);
		if(Height(T->Left)-Height(T->Right)==2)
		{	
			if(X<T->Left->Element)
				T=SingleRotateWithLeft(T);
			else
				T=DoubleRotateWithLeft(T);
		}
	}else if(X>T->Element){
		T->Right=Insert(X,T->Right);
		if(Height(T->Right)-Height(T->Left)==2)
		{
			if(X>T->Right->Element)
				T=SingleRotateWithRight(T);
			else
				T=DoubleRotateWithRight(T);
		}
	}
	if(Height(T->Left)>=Height(T->Right))
		T->Height=Height(T->Left)+1;
	else
		T->Height=Height(T->Right)+1;
	return T;
}
void PrintInorder(AVLTree T)
{
	if(T)
	{
		PrintInorder(T->Left);
		printf("%d(%d) ",T->Element,T->Height);
		PrintInorder(T->Right);
	}
}
int Height(Position P)
{
	if(P==NULL)
		return -1;
	else
		return P->Height;
}
int Max(int num1,int num2)
{
	if(num1>=num2)
		return num1;
	return num2;
}
void DeleteTree(AVLTree T){
	if(T->Left!=NULL)
		DeleteTree(T->Left);
	if(T->Right!=NULL)
		DeleteTree(T->Right);
	free(T);
}
