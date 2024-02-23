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

void swap_buffers(BUFFER** buffer_1, BUFFER** buffer_2){
	BUFFER* temp = *buffer_1;
	*buffer_1 = *buffer_2;
	*buffer_2 = temp;
	return;
}
