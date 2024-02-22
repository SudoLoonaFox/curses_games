#include<ncurses.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

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

// TODO look for bug in this or next function
int cell_state(BUFFER* buffer, int h, int w){
	if(w<0 || w >= buffer->width){
		return -1;
	}
	if(h<0 || h >= buffer->height){
		return -1;
	}
	return buffer->buffer[buffer->width*h+w];
}

int moore_neighbours(BUFFER* buffer, int h, int w, int test_val){
	int neighbours = 0;
	if(cell_state(buffer, h+1, w-1)==test_val){
		neighbours++;// NW
	}
	if(cell_state(buffer, h+1, w)==test_val){
		neighbours++; // N
	}
	if(cell_state(buffer, h+1, w+1)==test_val){
		neighbours++; // NE
	}
	if(cell_state(buffer, h, w-1)==test_val){
		neighbours++; // W
	}
	if(cell_state(buffer, h, w+1)==test_val){
		neighbours++; // E
	}
	if(cell_state(buffer, h-1, w-1)==test_val){
		neighbours++; // SW
	}
	if(cell_state(buffer, h-1, w)==test_val){
		neighbours++; // S
	}
	if(cell_state(buffer, h-1, w+1)==test_val){
		neighbours++; // SE
	}
	return neighbours;
}
void draw_buffer(WINDOW* win, BUFFER* buffer, chtype* symbols){
	wmove(win, 0,0);
	for(int i = 0; i < buffer->height * buffer->width; i++){
		waddch(win, symbols[buffer->buffer[i]]);
		// waddch(win, ACS_DIAMOND);
	}
}

void conway_life_random(BUFFER* buffer){
	for(int i = 0; i < buffer->width*buffer->height; i++){
		buffer->buffer[i] = rand()%2;
	}
}

void conway_life_tick(BUFFER* buffer, BUFFER* new_buffer){
	if(buffer->height*buffer->width != new_buffer->height*new_buffer->width){
		return;
	}
	int n;
	for(int i = 0; i < buffer->height*buffer->width; i++){
		n = moore_neighbours(buffer, i/buffer->width, i%buffer->width, 1);
		if(n<2){
			new_buffer->buffer[i] = 0;
			continue;
		}
		if(n==3){
			new_buffer->buffer[i] = 1;
			continue;
		}
		if(n>3){
			new_buffer->buffer[i] = 0;
			continue;
		}
	}
}

void swap_buffers(BUFFER** buffer_1, BUFFER** buffer_2){
	BUFFER* temp = *buffer_1;
	*buffer_1 = *buffer_2;
	*buffer_2 = temp;
	return;
}

int main(){
	// TODO add colors
	setlocale(LC_ALL, "");
	srand(time(NULL));
	initscr(); // init screen
	cbreak(); // disable character buffering
	noecho(); // supress auto echo of typed characters
	keypad(stdscr, true); // capture special keys
	curs_set(0);
	chtype wireworld_symbols[] = {ACS_BLOCK, ACS_BOARD, ACS_DIAMOND, ACS_PLUS};

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

	/*for(int i = 0; i < height*width; i++){
		front_buffer->buffer[i] = i%2;
	}*/
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
