#include <stdio.h>
#include <stdlib.h>

 int main(int argc, char* argv[]){
	int n;
	char** name;

	n=atoi(argv[1]);
	
	printf("enter %d names: ",n);
	name=(char**)malloc(sizeof(char*)*n);

	for(int i=0;i<n;i++)
		name[i]=(char*)malloc(sizeof(char*)*35);
	for(int i=0;i<n;i++)
		scanf("%s",name[i]);
	for(int i=0;i<n;i++)
		printf("%s\n",name[i]);
	
	for(int i=0;i<n;i++)
		free(name[i]);
	free(name);

	return 0;
}
