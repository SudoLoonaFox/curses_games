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
			if(moore_neighbours(buffer, y+1, x, 1) <= 2){
				options[options_len++] = 1;
			}
		}
		if(cell_state(buffer, y-1, x) == 0){
			if(moore_neighbours(buffer, y-1, x, 1) <= 2){
				options[options_len++] = 2;
			}
		}
		if(cell_state(buffer, y, x-1) == 0){
			if(moore_neighbours(buffer, y, x-1, 1) <= 2){
				options[options_len++] = 3;
			}
		}
		if(cell_state(buffer, y, x+1) == 0){
			if(moore_neighbours(buffer, y, x+1, 1) <= 2){
				options[options_len++] = 4;
			}
		}
		if(options_len > 0){
			switch(options[rand()%(options_len)]){
				case 1:
					y++;
					break;
				case 2:
					y--;
					break;
				case 3:
					x--;
					break;
				case 4:
					x++;
					break;
			}
			buffer->buffer[x + y * buffer->width] = 1;
			stack[stack_len++] = x + y * buffer->width;
			continue;
		}

		int t = stack[--stack_len];
		x = t%buffer->width;
		y = (int)t/buffer->width;
	}
}


/*void generate_maze(BUFFER* buffer){
	// NOTE y and x are swapped for this buffer due to how curses deals with windows
	int* stack = malloc(sizeof(int)*buffer->height*buffer->width);
	for(int i = 0; i < buffer->height*buffer->width; i++){
		stack[i] = 0;
	}
	int stack_len = 0;
	int x = buffer->width/2;
	int y = buffer->height/2;
	buffer->buffer[x+y*buffer->width] = 1;
	stack[stack_len++] = x+y*buffer->width; // string length has number of items in stack but the indexing is done before adding the item so it starts at zero. popping items off the stack will be done with --stack_len instead so the indexes are right
	while(stack_len > 0){
		// to ensure spaces lines can only be drawn along even axises. The start position will always be even because dividing integers by 2 is always even due to truncation
		int options[4] = {};
		int options_len = 0;
		if(x % 2 == 0){
			if(y % 2 == 0){ // if x and y are both even you can move in any direction that is empty
				// n 1 s 2 e 3 w 4
				if(cell_state(buffer, y+1, x) == 0){// N
					options[options_len++] = 1;
					if(moore_neighbours(buffer, y+1, x, 1) == 1){
					}
				}
				if(cell_state(buffer, y-1, x) == 0){// S
					options[options_len++] = 2;
					if(moore_neighbours(buffer, y-1, x, 1) == 1){
					}
				}
				if(cell_state(buffer, y, x+1) == 0){// E
					options[options_len++] = 3;
					if(moore_neighbours(buffer, y, x+1, 1) == 1){
					}
				}
				if(cell_state(buffer, y, x-1) == 0){// W
					options[options_len++] = 4;
					if(moore_neighbours(buffer, y, x-1, 1) == 1){
					}
				}
			}
			else{
				if(cell_state(buffer, y+1, x) == 0){// N
					options[options_len++] = 1;
					if(moore_neighbours(buffer, y+1, x, 1) == 1){
					}
				}
				if(cell_state(buffer, y-1, x) == 0){// S
					options[options_len++] = 2;
					if(moore_neighbours(buffer, y-1, x, 1) == 1){
					}
				}
			}
		}
		else{
			if(cell_state(buffer, y, x+1) == 0){// E
				options[options_len++] = 3;
				if(moore_neighbours(buffer, y, x+1, 1) == 1){
				}
			}
			if(cell_state(buffer, y, x-1) == 0){// W
				options[options_len++] = 4;
				if(moore_neighbours(buffer, y, x-1, 1) == 1){
				}
			}
		}
		if(options_len > 0){
			int choice = (rand()% options_len);
			switch(options[choice]){
				case 1:
					y++;
					break;
				case 2:
					y--;
					break;
				case 3:
					x--;
					break;
				case 4:
					x++;
					break;
			}
			buffer->buffer[x+y*buffer->width] = 1;
			stack[stack_len++] = x+y*buffer->width;
		}
		else{
			if(stack_len>0){
				int a = stack[--stack_len];
				x = a - a/buffer->width;
				y = a/buffer->width;
			}
		}
	}
	free(stack);	
}
*/
void fps_game(WINDOW* win, int height, int width, chtype* symbols, int len){
	BUFFER* buffer = create_buffer(height, width);
	generate_maze(win, buffer, symbols);
	draw_buffer(win, buffer, symbols);
	wrefresh(win);
	while(1);
	free_buffer(buffer);
}
