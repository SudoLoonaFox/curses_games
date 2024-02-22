#include<ncurses.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>

void screen_init(){
	setlocale(LC_ALL, "");
	srand(time(NULL));
	initscr(); // init screen
	cbreak(); // disable character buffering
	noecho(); // supress auto echo of typed characters
	keypad(stdscr, true); // capture special keys
	curs_set(0);
}

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

void swap_buffers(BUFFER** buffer_1, BUFFER** buffer_2){
	BUFFER* temp = *buffer_1;
	*buffer_1 = *buffer_2;
	*buffer_2 = temp;
	return;
}

// TODO replace cursor with color when color is added
void editor(WINDOW* win, BUFFER* buffer, chtype* symbols, int num_symbols){
	chtype cursor = ACS_LANTERN;
	int c, h, w;
	int height = buffer->height;
	int width = buffer->width;
	h = height/2;
	w = width/2;
	do{
	draw_buffer(win, buffer, symbols);
	mvwaddch(win, h, w, cursor); // cursor
	wrefresh(win);
	c = getch();
	if(c == KEY_RIGHT){
		if(w+1 < width){
			w++;
		}
	}
	if(c == KEY_LEFT){
		if(w-1 >= 0){
			w--;
		}
	}
	if(c == KEY_DOWN){
		if(h+1 < height){
			h++;
		}
	}
	if(c == KEY_UP){
		if(h-1 >= 0){
			h--;
		}
	}
	if(c == ' '){
		if(buffer->buffer[w+h*width] == 3){
			buffer->buffer[w+h*width] = 0;
		}
		buffer->buffer[w+h*width] = 3;
	}
	if(c == '1'){
		buffer->buffer[w+h*width] = 1;
	}

	if(c == KEY_BACKSPACE){
		buffer->buffer[w+h*width] = 0;
	}

	}
	while(c != 'c');
}

