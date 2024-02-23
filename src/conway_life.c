#include<ncurses.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>

#include"graphics_tools.h"

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

void conways_game_of_life(WINDOW* win, int height, int width, chtype* symbols){
	BUFFER* front_buffer = create_buffer(height, width);
	BUFFER* back_buffer = create_buffer(height, width);
	conway_life_random(front_buffer);
	while(getch() != 'q'){
		if(getch() == 'r'){
			conway_life_random(front_buffer);
		}
		/*if(getch() == 'p'){
			while(getch() != 'p'); // TODO fix this to add quit when paused
		}*/
		conway_life_tick(front_buffer, back_buffer);
		draw_buffer(win, front_buffer, symbols);
		swap_buffers(&front_buffer, &back_buffer);
		wrefresh(win);
		delay(100);
	}
	free_buffer(front_buffer);
	free_buffer(back_buffer);
}

