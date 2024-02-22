#ifndef CONWAY_LIFE_H
#define CONWAY_LIFE_H

#include<stdlib.h>
#include<locale.h>
#include<time.h>

#include"graphics_tools.h"

void conway_life_random(BUFFER* buffer);

void conway_life_tick(BUFFER* buffer, BUFFER* new_buffer);

#endif
