#include <stdio.h>
#include <stdlib.h>

int number[10];
int length;

void rotate(int * array,int len){

	int temp = array[0];
	for (int i = 0; i<len-1; i++) {
		array[i] = array[i+1];
	}
	array[len-1] = temp;
}

void printarray(void){

	for (int i = 0; i < length ; i++) {
		printf("%d",number[i]);
	}
	printf("\n");
}


void combination(int* array,int n){

	int count = n;
	if (n == 2) {
		rotate(array,n);
		printarray();
		rotate(array,n);
		printarray();
		return;
	}
	while ( count-- ) {
		rotate(array,n);
		combination(array+1,n-1);
	}
}


int main (int argc, const char * argv[]) {
	
	puts("Enter length of number");
	scanf("%d",&length);
	
	for (int i = 0; i < length; i++) {
		scanf("%d",&number[i]);
	}
	combination(number,length);
	
	return 0;
}
