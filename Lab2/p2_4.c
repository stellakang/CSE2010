#include <stdio.h>
#include <stdlib.h>


int add(int, int);
int sub(int, int);
int mul(int, int);
int divi(int, int);

int (*oper[4])(int, int)= { add, sub, mul, divi };

int main(int argc, char** argv)
{
	int i = 0;
	int a, b, n;
	while(true)
	{
		
		printf("====================\n");
		printf("0. add\n");
		printf("1. sub\n");
		printf("2. mul\n");
		printf("3. div\n");
		printf("4. exit\n");
		printf("====================\n");
		printf("Select Operation :");
		if (i == 0) {
			n=atoi(argv[1]);
			printf("%d\n", n);
		}
		else scanf("%d", &n);

		if(n==4)
			break;

		printf("Input 2 operand :");
		
		if(i == 0){
			a=atoi(argv[2]);
			b=atoi(argv[3]);
			printf("%d %d\n",a,b);
		}
		else scanf("%d%d", &a, &b);
		printf("Result = %d\n",oper[n](a,b));

		i = 1;
	}

	return 0;
}

int add(int a, int b) { return a+b; }
int sub(int a, int b) { return a-b; }
int mul(int a, int b) { return a*b; }
int divi(int a, int b) { return a/b; }
