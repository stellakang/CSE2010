#include <stdio.h>

char input[35];

int main()
{
	printf("enter your name:\n");
	fgets(input,35,stdin); 
	printf("your name is %s\n",input);	
	return 0;
}
