#include <stdio.h>


int mul_of_3(int num){

	return (num%3 ==0) ? 1 : 0;
}

int mul_of_5(int num){
	
	return (num%5 ==0) ? 1 : 0;
}

int main(void) {
	
	int sum = 0,top = 0;
	
	puts("Enter the top limit");
	scanf("%d",&top);
	for (int i = 0; i < top ; i++) {
		if (mul_of_3(i) || mul_of_5(i)) {
			sum+=i;
		}
	}
	printf("%d",sum);
	
}