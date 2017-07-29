#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int STARTX = 0;
int STARTY = 0;
int ENDX = 9;
int ENDY = 9;

#define CELL_CHAR '#'
#define TIME_OUT  300

typedef struct _state {
	int oldstate;
	int newstate;
}state;

void display(WINDOW *win, state **area, int startx, int starty, int endx, int endy);
void calc(state **area, int x, int y);
void update_state(state **area, int startx, int starty, int endx, int endy);

int main()
{	state **workarea;
	int i, j;
	
	initscr();
	cbreak();
	timeout(TIME_OUT);
	

	workarea = (state **)calloc(ENDY+1, sizeof(state *));
	for(i = 0;i < ENDY+1; ++i)
		workarea[i] = (state *)calloc(ENDX+1, sizeof(state));

	 
	/* For inverted U */
	workarea[0][1].newstate = TRUE;
	workarea[0][2].newstate = TRUE;
	workarea[1][1].newstate = TRUE;
	workarea[1][3].newstate = TRUE;
	workarea[1][4].newstate = TRUE;
	workarea[2][3].newstate = TRUE;
	workarea[2][5].newstate = TRUE;
	//update_state(workarea, STARTX, STARTY, ENDX, ENDY);
	
	/* For block  */

	//workarea[37][13].newstate = TRUE;
	//workarea[37][14].newstate = TRUE;
	//workarea[38][13].newstate = TRUE;
	//workarea[38][14].newstate = TRUE;

	update_state(workarea, STARTX, STARTY, ENDX, ENDY);
    WINDOW* mywin = newwin(ENDX, ENDY, STARTY, STARTX);
	keypad(mywin, TRUE);
	display(mywin, workarea, STARTX, STARTY, ENDX, ENDY);
	while(getch() != KEY_F(1))
	{	for(i = STARTX; i <= ENDX; ++i)
			for(j = STARTY; j <= ENDY; ++j)
				calc(workarea, i, j);
		update_state(workarea, STARTX, STARTY, ENDX, ENDY);
		display(mywin,  workarea, STARTX, STARTY, ENDX, ENDY);	
	}
	
	endwin();
	return 0;
}	

void display(WINDOW *win, state **area, int startx, int starty, int endx, int endy)
{	int i, j;
	wclear(win);
	for(i = startx; i <= endx; ++i)
		for(j = starty;j <= endy; ++j)
			if(area[i][j].newstate == TRUE)
				mvwaddch(win, j, i, CELL_CHAR);
	wrefresh(win);
}

void calc(state **area, int i, int j)
{	int neighbours;
	int newstate;
 	
	neighbours	= 
		area[(i - 1 + 9) % 9][j].oldstate		+
		area[(i - 1 + 9) % 9][(j - 1 + 9) % 9].oldstate 	+
		area[(i - 1 + 9) % 9][(j + 1) % 9].oldstate 	+
		area[(i + 1) % 9][j].oldstate		+
		area[(i + 1) % 9][(j - 1 + 9) % 9].oldstate 	+
		area[(i + 1) % 9][(j + 1) % 9].oldstate 	+
		area[i][(j - 1 + 9) % 9].oldstate		+
		area[i][(j + 1) % 9].oldstate;
	
	newstate = FALSE;
	if(area[i][j].oldstate == TRUE && (neighbours == 2 || neighbours == 3))
		 newstate = TRUE;
	else
		if(area[i][j].oldstate == FALSE && neighbours == 3)
			 newstate = TRUE;
	area[i][j].newstate = newstate;
}

void update_state(state **area, int startx, int starty, int endx, int endy)
{	int i, j;
	
	for(i = startx; i <= endx; ++i)
		for(j = starty; j <= endy; ++j)
			area[i][j].oldstate = area[i][j].newstate;
}	
