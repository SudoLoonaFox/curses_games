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


void wireworld(WINDOW* win, int height, int width, chtype* symbols, int len){
	BUFFER* buffer_front = create_buffer(height, width);
	BUFFER* buffer_back = create_buffer(height, width);
	// TODO add differernt symbols for editing
	editor(win, buffer_front, symbols, 4);
	while(getch() != 'q'){
		if(getch() == 'e'){
			editor(win, buffer_front, symbols, 4);
		}
		draw_buffer(win, buffer_front, symbols);
		wrefresh(win);
		wireworld_tick(buffer_front, buffer_back);
		swap_buffers(&buffer_front, &buffer_back);
		delay(100); // Replace delay with option that allows quitting without waiting
	}
	free_buffer(buffer_front);
	free_buffer(buffer_back);
}
