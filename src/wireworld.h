#ifndef WIREWORLD_H
#define WIREWORLD_H

#include<ncurses.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>

#include"graphics_tools.h"

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

void wireworld_random(BUFFER* buffer);


void wireworld_tick(BUFFER* buffer, BUFFER* new_buffer);


#endif
