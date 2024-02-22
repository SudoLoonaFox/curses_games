#include<ncurses.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>

#include"graphics_tools.h"

void wireworld_random(BUFFER* buffer){
	for(int i = 0; i < buffer->width*buffer->height; i++){
		buffer->buffer[i] = rand()%4;
	}
}

/*
0 empty
1 head
2 tail
3 conductor
empty → empty,
electron head → electron tail,
electron tail → conductor,
conductor → electron head if exactly one or two of the neighbouring cells are electron heads, otherwise remains conductor.
*/

void wireworld_tick(BUFFER* buffer, BUFFER* new_buffer){
	if(buffer->height*buffer->width != new_buffer->height*new_buffer->width){
		return;
	}
	int n;
	for(int i = 0; i < buffer->height*buffer->width; i++){
		if(buffer->buffer[i] == 0){ // if empty
			new_buffer->buffer[i] = 0;
			continue;
		}
		if(buffer->buffer[i] == 1){ // if head then become tail
			new_buffer->buffer[i] = 2;
			continue;
		}
		if(buffer->buffer[i] == 2){ // if tail then become conductor
			new_buffer->buffer[i] = 3;
			continue;
		}
		if(buffer->buffer[i] == 3){ // if tail then become conductor
			n = moore_neighbours(buffer, i/buffer->width, i%buffer->width, 1);
			if(n>0 && n<3){
				new_buffer->buffer[i] = 1;
				continue;
			}
			new_buffer->buffer[i] = 3;
			continue;
		}
	}
}

