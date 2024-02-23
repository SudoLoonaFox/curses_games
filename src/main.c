#include<ncurses.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>


#include"graphics_tools.h"
#include"conway_life.h"
#include"wireworld.h"
#include"mandelbrot.h"
#include"maze.h"

int main(){
	screen_init();
	chtype wireworld_symbols[] = {ACS_BOARD, ACS_BLOCK, ACS_DIAMOND, ACS_PLUS };

	int height, width;
	getmaxyx(stdscr, height, width);
	WINDOW* win = newwin(height, width, 0, 0);

	BUFFER* front_buffer = create_buffer(height, width);
	BUFFER* back_buffer = create_buffer(height, width);
	

	mandelbrot_set(front_buffer, 4);
	draw_buffer(win, front_buffer, wireworld_symbols);
	wrefresh(win);
	while(1);

	generate_maze(front_buffer);
	draw_buffer(win, front_buffer, wireworld_symbols);
	wrefresh(win);
	while(1);


	/*conway_life_random(front_buffer);

	while(1){
		conway_life_tick(front_buffer, back_buffer);
		draw_buffer(win, front_buffer, wireworld_symbols); 
		wrefresh(win);
		swap_buffers(&front_buffer, &back_buffer);
		delay(100);
	}*/

//	wireworld_random(front_buffer);
//	mandelbrot_set(back_buffer, 4);
//	draw_buffer(win, back_buffer, wireworld_symbols);
//	wrefresh(win);
//	getch();
	// editor(win, front_buffer, wireworld_symbols, 4);
	while(1){
		wireworld_tick(front_buffer, back_buffer);
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
