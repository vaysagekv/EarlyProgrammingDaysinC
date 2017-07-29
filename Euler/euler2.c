#include <stdio.h>

int main(void) {
	
	int sum = 0,top = 0;
	int fib1 = 1,fib2 = 1,fib = 0;
	
	puts("Enter the top limit");
	scanf("%d",&top);
	while (fib < top) {
		fib = fib1+fib2;
		fib1 = fib2;
		fib2 = fib;
		if (fib % 2 == 0) {
			sum += fib;
		}
	}
	printf("%d\n",sum);
	
}