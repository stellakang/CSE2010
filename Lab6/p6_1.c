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
			fscanf(fi,"%d",&key);
			//deleteNode(root,key);
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
void printInorder(Tree* root)
{

}
void printPreorder(Tree* root)
{

}
void printPostorder(Tree* root)
{

}
