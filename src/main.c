#include<ncurses.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>


#include"graphics_tools.h"
#include"conway_life.h"

int main(){
	screen_init();
	chtype wireworld_symbols[] = {ACS_BLOCK, ACS_BOARD, ACS_DIAMOND, ACS_PLUS};

	int height, width;
	getmaxyx(stdscr, height, width);
	WINDOW* win = newwin(height, width, 0, 0);

	BUFFER* front_buffer = create_buffer(height, width);
	BUFFER* back_buffer = create_buffer(height, width);

	conway_life_random(front_buffer);

	while(1){
		conway_life_tick(front_buffer, back_buffer);
		draw_buffer(win, front_buffer, wireworld_symbols); 
		wrefresh(win);
		swap_buffers(&front_buffer, &back_buffer);
		delay(100);
	}
	while(1);
	free_buffer(front_buffer);
	free_buffer(back_buffer);
	// exiting
	endwin();
	return 0;
}
