#ifndef GRAPHICS_TOOLS_H
#define GRAPHICS_TOOLS_H

void screen_init();

void delay(int number_of_seconds);

typedef struct{
	int* buffer;
	int height;
	int width;
}BUFFER;

BUFFER* create_buffer(int height, int width);

void free_buffer(BUFFER* buffer);

int cell_state(BUFFER* buffer, int h, int w);

int moore_neighbours(BUFFER* buffer, int h, int w, int test_val);

void draw_buffer(WINDOW* win, BUFFER* buffer, chtype* symbols);

void swap_buffers(BUFFER** buffer_1, BUFFER** buffer_2);

#endif
