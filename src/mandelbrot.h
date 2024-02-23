#ifndef MANDELBROT_H
#define MANDELBROT_H

#include"graphics_tools.h"

#define MAX_ITER 50

void mandelbrot_set(WINDOW* win, int height, int width, chtype* symbols, int len);
#endif
