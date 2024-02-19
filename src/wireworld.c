#include<ncurses.h>
#include<stdlib.h>

typedef struct{
	int* buffer;
	int height;
	int width;
}BUFFER;

BUFFER* create_buffer(int height, int width){
	BUFFER* buffer = malloc(sizeof(BUFFER));
	buffer->buffer = malloc(sizeof(int)*width*height);
	buffer->height = height;
	buffer->width = width;
	for(int i = 0; i < height*width; i++){
		buffer->buffer[i] = 0;
	}
	return buffer;
}

void free_buffer(BUFFER* buffer){
	free(buffer->buffer);
	free(buffer);
	return;
}

void draw_buffer(WINDOW* win, BUFFER* buffer, chtype* symbols){
	wmove(win, 0,0);
	for(int i = 0; i < buffer->height * buffer->width; i++){
		waddch(win, symbols[buffer->buffer[i]]);
	}
}

int main(){
	// init 
	// TODO add colors
	chtype wireworld_symbols[] = {' ', ACS_LANTERN, ACS_DIAMOND, ACS_PLUS};
	initscr(); // init screen
	cbreak(); // disable character buffering
	noecho(); // supress auto echo of typed characters
	keypad(stdscr, true); // capture special keys

	/*
	        (0,0)*----------------------------------* (0, COLUMNS-1)
             |                                  |
             |                                  |
             |    (y0,x0)                       |
             |      ---------------             |
             |      |             |             |
             |      |             |             |
             |      |     win     |nlines       |
             |      |             |             |
             |      |             |             |
             |      |             |             |
             |      ---------------             |
             |          ncols                   |
             |                                  |
             *----------------------------------*
       (LINES-1, 0)                              (LINES-1, COLUMNS-1)
	Here nline is the height of the window -- number of lines, ncols is the width -- number of columns of the window. y0 and x0 are the coordinates of the upper left corner of win on the screen -- line y0 and columns x0. You should make sure that the area of the new window is inside the screen.
	*/


	int height, width;
	getmaxyx(stdscr, height, width);
	// WINDOW* win = newwin(nlines, ncols, y0, x0);
	WINDOW* win = newwin(height, width, 0, 0);

	BUFFER* front_buffer = create_buffer(height, width);
	BUFFER* back_buffer = create_buffer(height, width);

	for(int i = 0; i < height*width; i++){
		front_buffer->buffer[i] = i % 4;
	}
	draw_buffer(win, front_buffer, wireworld_symbols); 


	while(1){
		wrefresh(win);
	}
	free(front_buffer);
	free(back_buffer);
	// exiting
	endwin();
	return 0;
}
