#include<ncurses.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>


#include"graphics_tools.h"
#include"conway_life.h"
#include"wireworld.h"
#include"mandelbrot.h"
#include"maze.h"

int main(int argc, char *argv[]){
	setlocale(LC_ALL, "");
	initscr();
 	srand(time(NULL));
	cbreak(); // disable character buffering
	noecho(); // supress auto echo of typed characters
	keypad(stdscr, true); // capture special keys
	curs_set(0);
	nodelay(stdscr, true);

	chtype wireworld_symbols[] = {ACS_BOARD, ACS_BLOCK, ACS_DIAMOND, ACS_PLUS };

	int height, width;
	getmaxyx(stdscr, height, width); // I hate macros
	WINDOW* win = newwin(height, width, 0, 0);

	// TODO change symbol set for game or include within game
	fps_game(win, height, width, wireworld_symbols, 4);

	conways_game_of_life(win, height, width, wireworld_symbols);

	delay(100);

	mandelbrot_set(win, height, width, wireworld_symbols, 4);
	
	delay(100);

	wireworld(win, height, width, wireworld_symbols, 4);

	// exiting
	endwin();
	return 0;
}
