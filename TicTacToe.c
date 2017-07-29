#include<stdio.h>
#include<stdlib.h>

#define UNUSEDPOS      '-'
#define ROW            3
#define COLUMN         3
#define GET_ROW(x)     ( ( (x)-1 ) / (ROW) )
#define GET_COLUMN(x)  ( ( (x)-1 ) % (COLUMN) )
#define POSITION(i,j)  ( ( (i)*ROW ) + (j) ) + 1
#define HUMAN          'X'
#define COMPUTER       'O'
#define WIN            'W'
#define TIE            'T'
#define NONE           'N'
#define INFINITY       10

char board[ROW][COLUMN];

unsigned int nodes_checked;

void init_board()
{
	for (unsigned short int i = 0; i < ROW; i++) {
		for (unsigned short int j = 0; j < COLUMN; j++) {
			board[i][j] = UNUSEDPOS;
		}
	}
}

void print_board()
{
	printf("\n\n\n\n");
	for ( unsigned short int i = 0; i < ROW; i++) {
		for (unsigned short int j = 0; j < COLUMN; j++) {
			printf("  %c  ",board[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n\n\n");
}

unsigned short int get_move()
{
	unsigned short int value = 0;
	printf("Enter Your Move ->");
	scanf("%hu",&value);
	return value;
}

unsigned short int is_valid(unsigned short int pos)
{
	if (pos > (ROW*COLUMN)) {
		return 0;
	}
	if (board[GET_ROW(pos)][GET_COLUMN(pos)] == UNUSEDPOS) {
		return 1;
	}
	else {
		return 0;
	}
}

void store_move(unsigned short int pos,char current_player)
{
	if (current_player == HUMAN) {
		board[GET_ROW(pos)][GET_COLUMN(pos)] = HUMAN ;
	}
	else if(current_player == COMPUTER)
	{
		board[GET_ROW(pos)][GET_COLUMN(pos)] = COMPUTER ;
	}
	else {
		board[GET_ROW(pos)][GET_COLUMN(pos)] = UNUSEDPOS ;
	}

}

char next_player(char player)
{
	return (player == HUMAN) ? COMPUTER : HUMAN ;
}


char check_winner(unsigned short pos,char current_player)
{
	unsigned short int current_row = GET_ROW(pos);
	unsigned short int current_col = GET_COLUMN(pos);
	
	int j = 0 ;
    
	if(board[current_row][j] == current_player
	   && board[current_row][j+1] == current_player
	   && board[current_row][j+2] == current_player)
	{
		return WIN;
	}
		
	
	if(board[j][current_col] == current_player
	   && board[j+1][current_col] == current_player
	   && board[j+2][current_col] == current_player)
	{
		return WIN;
	}

	
	if(board[0][0] == current_player
	   && board[1][1] == current_player
	   && board[2][2] == current_player)
	{
		return WIN;
	}
	
	if(board[2][0] == current_player
	   && board[1][1] == current_player
	   && board[0][2] == current_player)
	{
		return WIN;
	}
	
	for (int i = 0; i < ROW; i++) {
		for (j = 0; j < COLUMN; j++) {
			if (board[i][j] == UNUSEDPOS) {
				return NONE;
			}
		}
	}
	return TIE;
}

unsigned short int current_move_number;

short int get_best_move(unsigned short int* pos,char player,unsigned short int move_number)
{
	nodes_checked++;
	
	unsigned short int possible_moves = 0;
	unsigned short int possible_positions[ROW*COLUMN] = {0};
	short int best_score = player == HUMAN ? INFINITY :-INFINITY;
	unsigned short int best_pos = -1;
	
	for (int i = 0; i < ROW; i++) {
		for (int j = 0 ; j < COLUMN; j++) {
			if (board[i][j] == UNUSEDPOS) {
				possible_positions[possible_moves] = POSITION(i,j);
				possible_moves++;
			}
		}
	}

	while (possible_moves--) {
		short int score = 0;
		unsigned int checking_position = possible_positions[possible_moves];
		char value_from_check_winner;
		
		store_move(checking_position,player);
		value_from_check_winner = check_winner(checking_position,player);
		
		
		if (value_from_check_winner == WIN) {
			score = (COMPUTER == player) ? (INFINITY-move_number) : (-INFINITY+move_number);
		}
		else if (value_from_check_winner == TIE)
		{
			score = 0;
		}
		else {
			score = get_best_move(pos,next_player(player),move_number+1);
		}
		
		store_move(checking_position,UNUSEDPOS);
		
		if (player == COMPUTER) {
			
			if (score > best_score) {
				best_pos = checking_position;
				best_score = score;
			}
		}
		else if (player == HUMAN){
			if (score < best_score) {
				best_pos = checking_position;
				best_score = score;
			}
		}
	if ( current_move_number == move_number) {
			printf("Score = %hd bestscore = %hd ,Pos = %hu\n",score,best_score,checking_position);
		}
	}
	
	*pos = best_pos;
	return  best_score ;
}

void describe(short int score)
{
	if (score > 0) {
		printf("I can win by movenumber %d\n",INFINITY - score);
	}
	else if(score < 0)
	{
		printf("You will win by move %d\n",INFINITY + score);
	}
	else {
		printf("I wont lose\n");
	}

}

void TicTacToe()
{
	char current_player = COMPUTER;
	unsigned short int player_pos = -1;
	unsigned short int move_number = current_move_number = 1;
	
	
	init_board(board);
	do {
		system("clear");
		print_board();
		if (current_player == COMPUTER) {
			nodes_checked = 0;
			describe(get_best_move(&player_pos,current_player,move_number));
			printf("%hu its selec pos by computer",player_pos);
			printf("%u",nodes_checked);
			getchar();
		}
		else {
			do {
				player_pos = get_move();
			} while (!is_valid(player_pos));
		}
        
		store_move(player_pos,current_player);
		move_number++;
		current_move_number = move_number;
	} while ( (check_winner(player_pos,current_player) == NONE)
			  && (current_player = next_player(current_player)) );
	
	print_board();
	if (check_winner(player_pos,current_player) == TIE) {
		printf("Game Tied\n");
	}
	else {
		printf("Winner is %s\n",(current_player == HUMAN) ? "You" : "Computer");
	}

	
}

int main (void)
{
	char user_response[10];
	
	do {
		TicTacToe();
		printf("Do you want to play again-->");
		scanf("%s",user_response);
	} while ( (user_response[0]=='Y') || (user_response[0]=='y'));// Make change to remove the bug ...
    
	
	/*
	unsigned short int move_number = 5;
	current_move_number = 5;
	
	board[0][0] = UNUSEDPOS;
	board[0][1] = UNUSEDPOS;
	board[0][2] = HUMAN;
	board[1][0] = UNUSEDPOS;
	board[1][1] = UNUSEDPOS;
	board[1][2] = COMPUTER;
	board[2][0] = UNUSEDPOS;
	board[2][1] = COMPUTER;
	board[2][2] = HUMAN;
	
	char current_player = HUMAN;
	unsigned short int player_pos = -1;
	get_best_move(&player_pos,current_player,move_number);
	printf("%hu",player_pos);
	*/
	 
}

