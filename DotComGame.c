#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VERTICAL 0
#define HORIZONTAL 1

#define NOTUSED 'N'
#define MISS 'M'
#define HIT 'H'

#define BOARDSIZE 7
#define TOTALDOTCOMS 3
#define DOTCOMLEN 3
#define MAXHITS DOTCOMLEN

typedef struct  {
	char* name;
	short hits;
	short pos_in_array[DOTCOMLEN];
}Dotcom;


char board[BOARDSIZE * BOARDSIZE];
Dotcom dotcoms[TOTALDOTCOMS] = { {"popeye.com",0,{-1,-1,-1}},
								 {"olive.com",0,{-1,-1,-1}},
								 {"pluto.com",0,{-1,-1,-1}}   };


void init_board() {

	int i ;
	for (i = 0; i < BOARDSIZE * BOARDSIZE; i++) {
		board[i] = NOTUSED ;
	}
}


int already_used_postions(int current_dotcom) {
	int i ,j, k;
	for (i = 0; i < TOTALDOTCOMS; i++) {
		if (i == current_dotcom) continue;
		for (j = 0; j < DOTCOMLEN; j++) {
			for (k = 0; k < DOTCOMLEN; k++) {
				if (dotcoms[current_dotcom].pos_in_array[j] == 
					dotcoms[i].pos_in_array[k] )
					return 1;
				
			}
		}
	}
	return 0;
	
}


void arrange_dotcoms() {
	
	int i = 0;
	srand(time(NULL));
	
	while (i < TOTALDOTCOMS) {
		int alignment = rand() % 2;  // alignment = 1 for horizontal ,0 for vertical
		int position = rand() % (BOARDSIZE * BOARDSIZE);
		dotcoms[i].pos_in_array[0] = position;

		if (alignment == HORIZONTAL) {
			dotcoms[i].pos_in_array[1] = (position + 1) % (BOARDSIZE * BOARDSIZE);
			dotcoms[i].pos_in_array[2] = (position + 2) % (BOARDSIZE * BOARDSIZE);
		}else if (alignment == VERTICAL) {
			dotcoms[i].pos_in_array[1] = (position + BOARDSIZE) % (BOARDSIZE * BOARDSIZE);
			dotcoms[i].pos_in_array[2] = (position + BOARDSIZE + BOARDSIZE) % (BOARDSIZE * BOARDSIZE);
		}
		if (already_used_postions(i)) continue;
		i++;
	}
}

int game_over() {

	int i ;
	for (i = 0; i < TOTALDOTCOMS; i++) {
		if (dotcoms[i].hits < MAXHITS) return 0; 
	}
	return 1;
}

int valid_input(int input) {

	if (input < 0 && input > (BOARDSIZE * BOARDSIZE) ) {
		return 0;
	}
	if (board[input] == NOTUSED )
		return 1;
	else
		return 0;
	
}

int is_hit (int pos ) {

	int i,j;
	for (i = 0; i < TOTALDOTCOMS; i++) {
		for (j = 0;  j < DOTCOMLEN; j++) {
			if (dotcoms[i].pos_in_array[j] == pos){
				printf("Hit %s\n",dotcoms[i].name);
				dotcoms[i].hits++;
				if (dotcoms[i].hits == MAXHITS)
					printf("Sunk %s\n",dotcoms[i].name);
				return 1;
			}
		}
	}
	return 0;	
}

void print_board() {

	int i;
	for (i = 0; i < (BOARDSIZE * BOARDSIZE) ; i++) {
		if (i % 7 == 0) printf("\n");
		if (board[i] == NOTUSED)
			printf("%d\t",i);
		else 
			printf("%c\t", board[i]);
	}
}

int get_user_input() {
	int input = -1;
	printf("\nEnter pos--->");
	scanf ("%d",&input);
	return input;
}


void start_game() {

	int user_input = -1;
	while (!game_over()) {
		
		print_board();
		do {
			user_input = get_user_input();
		}while (!valid_input(user_input));
		
		if (is_hit(user_input))
			board[user_input] = HIT ;
		else
			board[user_input] = MISS;
	}
	printf("\nGame Over\n");
}

int main(void) {
	
	init_board();
	arrange_dotcoms();
	start_game();
	
	return 0;
}