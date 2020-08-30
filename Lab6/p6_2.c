#include <stdio.h>
#include <stdlib.h>

typedef struct Tree{
	int value;
	struct Tree* left;
	struct Tree* right;
}Tree;

Tree* insertNode(Tree *root, int key);
Tree* deleteNode(Tree *root, int key);
Tree* findNode(Tree *root, int key);
void printInorder(Tree* root);
void printPreorder(Tree* root);
void printPostorder(Tree* root);
Tree* FindMin(Tree* root);
Tree* FindMax(Tree* root);
void DeleteTree(Tree* root);

int  delSuccess=0;

void main(int argc,char* argv[])
{
	FILE *fi=fopen(argv[1],"r");
	char cv;
	int key;

	Tree* root=NULL;

	while(!feof(fi))
	{
		fscanf(fi,"%c",&cv);
		switch(cv){
		case 'i':
			fscanf(fi,"%d",&key);
			root=insertNode(root,key);
			break;
		case 'd':
			delSuccess=0;
			fscanf(fi,"%d",&key);
			deleteNode(root,key);
			if(delSuccess)
				printf("Delete %d\n",key);
			break;
		case 'f':
			fscanf(fi,"%d",&key);
			findNode(root,key);
			break;
		case 'p':
			fscanf(fi,"%c",&cv);
			if(cv=='i')
				printInorder(root);
			else if(cv=='r')
				printPreorder(root);
			else if(cv=='o')
				printPostorder(root);
			printf("\n");
			break;
		}
	}
	DeleteTree(root);
	fclose(fi);
	
}
Tree* insertNode(Tree* root,int key)
{
		if(root==NULL)
		{		
			root=malloc(sizeof(struct Tree));
			if(root==NULL)
				printf("Out of space!\n");
			else
			{
				root->value=key;
				root->left=root->right=NULL;
				printf("insert %d\n",key);
			}
		}
		else if(key<root->value)
		{
			root->left=insertNode(root->left,key);
		}
		else if(key>root->value)
		{
			root->right=insertNode(root->right,key);
		}
		else if(key==root->value)
			printf("Insertion Error : There is already %d in the tree.\n",key);

		return root;
}
Tree* deleteNode(Tree *root, int key)
{
	Tree* Tmp;
	
	if(root==NULL)
		printf("Deletion error : %d is not in the tree.\n",key);
	else if(key<root->value)
		root->left=deleteNode(root->left,key);
	else if(key>root->value)
		root->right=deleteNode(root->right,key);
	else if(root->left&&root->right)
	{
		Tmp=FindMax(root->left);
		root->value=Tmp->value;
		root->left=deleteNode(root->left,root->value);
		delSuccess=1;
	}
	else
	{
		Tmp=root;
		if(root->left==NULL)
			root=root->right;
		else if(root->right==NULL)
			root=root->left;
		delSuccess=1;
		free(Tmp);
	}	

	return root;
}
Tree* findNode(Tree *root, int key)
{
	if(root==NULL)
	{
		printf("%d is not in the tree.\n",key);
		return NULL;
	}
	if(key<root->value)
		return findNode(root->left,key);
	else if(key>root->value)
		return findNode(root->right,key);
	else
	{
		printf("%d is in the tree.\n",key);
		return root;
	}
}
Tree* FindMax(Tree* root)
{
	if(root==NULL)
		return NULL;
	else
		while(root->right!=NULL)
			root=root->right;
	
	return root;
}
Tree* FindMin(Tree* root)
{
	if(root==NULL)
		return NULL;
	else
		while(root->left!=NULL)
			root=root->left;	
	
	return root;
}

void printInorder(Tree* root)
{
	if(root->left!=NULL)
		printInorder(root->left);
	printf("%d ",root->value);
	if(root->right!=NULL)
		printInorder(root->right);
}
void printPreorder(Tree* root)
{
	printf("%d ",root->value);
	if(root->left!=NULL)
		printPreorder(root->left);
	if(root->right!=NULL)
		printPreorder(root->right);
}
void printPostorder(Tree* root)
{
	if(root->left!=NULL)
		printPostorder(root->left);
	if(root->right!=NULL)
		printPostorder(root->right);
	printf("%d ",root->value);
}
void DeleteTree(Tree* root)
{
	if(root->left!=NULL)
		DeleteTree(root->left);
	if(root->right!=NULL)
		DeleteTree(root->right);
	free(root);
}
