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

