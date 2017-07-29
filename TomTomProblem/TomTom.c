#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


#define MAXARRAYSIZE 30

char* get_row(void){
	short count = 0;
	char* row =  malloc(MAXARRAYSIZE);
	puts("Enter Row");
	char c;
	while ( (c = getchar()) != '}' ) {
		if(isalpha(c))
			row[count++] = c;
	}
	row[count] = '\0';
	return row;
}

unsigned short are_rows_same(char* row1,char* row2,unsigned short offset,int len){
	int i = 0 , j = offset;
	while (i<len) {
		if (row1[i++] != row2[j++%len])
			return 0;
	}
	return 1;
}

int main (void) {

	unsigned short same_rows = 0;
	char* row1 = get_row();
	char* row2 = get_row();
	
	if (strlen(row1) == strlen(row2) ) {
		char* starting_char = strchr(row2,row1[0]);
		while ( starting_char != NULL ) {
			unsigned short offset = starting_char - row2;
			same_rows = are_rows_same(row1,row2,offset,strlen(row1));
			if (same_rows) break;
			starting_char = strchr(starting_char+1,row1[0]); /* Check from next position */
		}
	}
	same_rows ? puts("Rows are same") : puts("Rows are different");
	free(row1);
	free(row2);
	return 0;
}

