#include <ncurses.h>
#include <time.h>

#define PADDLE_WIDTH 5
#define MOVE_RATE 2
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
	halfdelay(MOVE_RATE);
	noecho();
	curs_set(0);
	twidth = random(PADDLE_WIDTH * 2 + P_STEP, COLS - 30);
	theight = random(5, ((twidth + 5 > LINES) ? (LINES - 4) : (twidth)));
	int winx, winy, wwidth, wheight;
	wwidth = twidth + 2;
	wheight = theight + 3;
	winy = (LINES - wheight) / 2;
	winx = (COLS - wwidth) / 2 + 10;
	paddlex = random(1, twidth + 2 - PADDLE_WIDTH);
	ballx = random(paddlex, paddlex + PADDLE_WIDTH);
	bally = theight;
	balldir = random(0, 2) * 2 + 7;
	win = newwin(wheight, wwidth, winy, winx);
//	printw("%d x %d\n", twidth, theight);
//	printw("%d x %d\n", COLS, LINES);
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
		erase();
		mvprintw(0, 0, "(y, x): \t(%2d, %2d)", bally, ballx);
		mvprintw(1, 0, "Paddle: \t%2d to %d", paddlex, paddlex + PADDLE_WIDTH - 1); 
		mvprintw(2, 0, "Ball direction:\t %d", balldir);
		refresh();
		updatewin();
	}

//	halfdelay(0);
//	while (wgetch(win) != 'x') ;
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
	//from bounce.c
	//note - no contact with bat yet
	if ((balldir < 4) && (bally == theight)) {
		switch (balldir) {
			case 1:
				if (ballx == 1) {
					if (paddlex < 3) balldir = 9;
					else balldir = 3;
				} else if ((ballx > paddlex) && (ballx <= paddlex + PADDLE_WIDTH)) balldir = 7;
				break;
			case 3:
				if (ballx == twidth) {
					if (paddlex + PADDLE_WIDTH > theight - 1) balldir = 7;
					else balldir = 1;
				} else if ((ballx + 2 > paddlex) && (ballx + 1 < paddlex + PADDLE_WIDTH)) balldir = 9;
				break;
			default:
				break;

		}
	} else if ((ballx < 2) && (bally < 2)) {
		balldir = 3;
	} else if ((ballx > twidth - 1) && (bally < 2)) {
		balldir = 1;
	} else if ((ballx < 2) && ((balldir % 3) == 1)) {
		balldir += 2;
	} else if ((ballx > twidth - 1) && ((balldir % 3) == 0)) {
		balldir -= 2;
	} else if ((bally < 2) && (balldir > 6)) {
		balldir -= 6;
	} else if ((bally > theight) && (balldir < 4)) {
		balldir += 6;
	}
	switch (balldir) {
		case 1:
			bally++;
			ballx--;
			break;
		case 2:
			bally++;
			break;
		case 3:
			bally++;
			ballx++;
			break;
		case 4:
			ballx--;
			break;
		case 5:
			break;
		case 6:
			ballx++;
			break;
		case 7:
			bally--;
			ballx--;
			break;
		case 8:
			bally--;
			break;
		case 9:
			bally--;
			ballx++;
			break;
		default:
			break;
	}
	return 0;
}
