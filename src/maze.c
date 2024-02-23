#include<stdlib.h>
#include"graphics_tools.h"

typedef struct{
	int x;
	int y;
	float heading;
	int health;
	int speed;
}PLAYER;


void generate_maze(WINDOW* win, BUFFER* buffer, chtype* symbols){
	int* stack = malloc(sizeof(int)*buffer->height*buffer->width);
	int stack_len = 0;
	int x = buffer->width/2;
	int y = buffer->height/2;

	buffer->buffer[x + y * buffer->width] = 1;
	stack[stack_len++] = x + y * buffer->width;

	/*
	buffer->buffer[x + y * buffer->width] = 1;
	stack[stack_len++] = x + y * buffer->width;
	*/
	while(stack_len > 0){
		draw_buffer(win, buffer, symbols);
		wrefresh(win);
		delay(1);
		int options[4] = {};
		int options_len = 0;
		if(cell_state(buffer, y+1, x) == 0){
			if(cell_state(buffer, y+2, x) == 0){
				options[options_len++] = 1;
			}
		}
		if(cell_state(buffer, y-1, x) == 0){
			if(cell_state(buffer, y-2, x) == 0){
				options[options_len++] = 2;
			}
		}
		if(cell_state(buffer, y, x-1) == 0){
			if(cell_state(buffer, y, x-2) == 0){
				options[options_len++] = 3;
			}
		}
		if(cell_state(buffer, y, x+1) == 0){
			if(cell_state(buffer, y, x+2) == 0){
				options[options_len++] = 4;
			}
		}

		if(options_len > 0){
			switch(options[rand()%(options_len)]){
				case 1:
					y++;
					buffer->buffer[x + y * buffer->width] = 1;
					y++;
					buffer->buffer[x + y * buffer->width] = 1;
					stack[stack_len++] = x + y * buffer->width;
					break;
				case 2:
					y--;
					buffer->buffer[x + y * buffer->width] = 1;
					y--;
					buffer->buffer[x + y * buffer->width] = 1;
					stack[stack_len++] = x + y * buffer->width;
					break;
				case 3:
					x--;
					buffer->buffer[x + y * buffer->width] = 1;
					x--;
					buffer->buffer[x + y * buffer->width] = 1;
					stack[stack_len++] = x + y * buffer->width;
					break;
				case 4:
					x++;
					buffer->buffer[x + y * buffer->width] = 1;
					x++;
					buffer->buffer[x + y * buffer->width] = 1;
					stack[stack_len++] = x + y * buffer->width;
					break;
			}
			// stack[stack_len++] = x + y * buffer->width;
			continue;
		}
		int t = stack[--stack_len];
		x = t%buffer->width;
		y = (int)t/buffer->width;
	}
}

void fps_game(WINDOW* win, int height, int width, chtype* symbols, int len){
	BUFFER* buffer = create_buffer(height, width);
	generate_maze(win, buffer, symbols);
	draw_buffer(win, buffer, symbols);
	wrefresh(win);
	while(1);
	free_buffer(buffer);
}
