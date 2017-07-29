#include <stdio.h>
#include <stdlib.h>


typedef struct {
	unsigned short got_tail;
	unsigned int tosses;
} Person;

Person * persons;



void create_persons(int n) {
	persons = malloc(n * sizeof *persons);
	
	// initialise got_tail and tosses to zero;
	while (--n >= 0) {
		persons[n].got_tail = 0;
		persons[n].tosses = 0;
	}
}

void personal_toss(Person* p ) {
	srand(time(NULL));
	do {
		//0 for head 1 for tail;
		p->got_tail = (unsigned short)(((float)random()/((float)RAND_MAX + 1)) * 2);
		p->tosses++;
	} while (!p->got_tail);
	
}

void do_tosses(int n ) {
	
	
	int i ;
	for (i = 0; i < n ; i++) {
		personal_toss(&persons[i]);
	}
}

void print_result(int n) {
	
	int i;
	unsigned int total_tosses = 0;
	for (i = 0; i < n; i++) {
		printf("%d\t%d\n",i+1,persons[i].tosses);
		total_tosses += persons[i].tosses;
	}
	printf("\n\n\nTotal tosses = %d ,Total persons = %d, Average tosses = %f\n\n\n "
		   ,total_tosses,n,(float)total_tosses/n);
}

int main (int argc, const char * argv[]) {

	if (argc < 2) {
		printf("<usage> %s <No of persons to toss>\n\n",argv[0]);
		return 1;
	}
	int no_of_persons = atoi(argv[1]);
	
	create_persons(no_of_persons);
	do_tosses(no_of_persons);
	print_result(no_of_persons);
	
	return 0;
	
}
