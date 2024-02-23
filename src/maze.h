#ifndef MAZE_H
#define MAZE_H

#include<stdlib.h>
#include"graphics_tools.h"

typedef struct{
	int x;
	int y;
	float heading;
	int health;
	int speed;
}PLAYER;

void generate_maze(BUFFER* buffer);

void fps_game(WINDOW* win, int height, int width, chtype* symbols, int len);

#endif
