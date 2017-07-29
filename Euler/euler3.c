#include <stdio.h>

int is_prime(unsigned long long int number){
	
	for (unsigned long long int i = 2; i*i <= number; i++) {
		if (number % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main(void) {
	
	unsigned long long int number = 0;
	unsigned long long int largest_factor = 0;
	
	
	puts("Enter the Number");
	scanf("%llu",&number);
	
	for (unsigned long long int i = 2; i*i <= number; i++) {
		if (number % i == 0) {
			if (is_prime(i)) {
				largest_factor = i;
			}
		}
	}
	
	printf("%llu\n",largest_factor);
	
}