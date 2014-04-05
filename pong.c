#include <ncurses.h>
#include <time.h>

#define PADDLE_WIDTH 5
#define MOVE_RATE 5
#define P_STEP 2

int twidth, theight;
int bally, ballx;
int paddlex;
int balldir;
WINDOW * win;

int updatewin();
int random(int l, int h);
int moveball();


int main () {
	srand(time(NULL));
	initscr();
	cbreak();
//	halfdelay(MOVE_RATE);
	noecho();
	curs_set(0);
	twidth = random(10, COLS - 20);
	theight = random(5, ((twidth + 5 > LINES) ? (LINES - 4) : (twidth)));
	int winx, winy, wwidth, wheight;
	wwidth = twidth + 2;
	wheight = theight + 3;
	winy = (LINES - wheight) / 2;
	winx = (COLS - wwidth) / 2;
	paddlex = random(1, twidth + 2 - PADDLE_WIDTH);
	ballx = random(paddlex, paddlex + PADDLE_WIDTH);
	bally = theight;
	balldir = random(0, 2) * 2 + 7;
	win = newwin(wheight, wwidth, winy, winx);
	printw("%d x %d\n", twidth, theight);
	printw("%d x %d\n", COLS, LINES);
	refresh();
	updatewin();
	char ch;
	while (((ch = wgetch(win)) != 'x') && (bally < theight + 1)) {
		switch (ch) {
			case 'h':
				paddlex-= P_STEP;
				if (paddlex < 1) paddlex = 1;
				break;
			case 'l':
				paddlex+= P_STEP;
				if (paddlex > twidth + 1 - PADDLE_WIDTH) paddlex = twidth + 1 - PADDLE_WIDTH;
				break;
			default:
				break;

		}
		moveball();
		updatewin();
	}



	endwin();
	return 0;
}


int updatewin() {
	werase(win);
	box(win, 0, 0);
	mvwaddch(win, bally, ballx, '*');
	int i;
	for (i = 0; i < PADDLE_WIDTH; i++)
		mvwaddch(win, theight + 1, paddlex + i, '-');
	wrefresh(win);
	return 0;
}


int random(int l, int h) {
	return (rand() % (h - l)) + l;
}

int moveball() {
	//Add ball bouncing from bounce.c
	//Note - change indexes
	return 0;
}
