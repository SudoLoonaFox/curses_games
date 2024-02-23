#include"graphics_tools.h"

#define MAX_ITER 50

void mandelbrot_set(WINDOW* win, int height, int width, chtype* symbols, int len){
	BUFFER* buffer = create_buffer(height, width);	
	int i = 0;
	for(double y0 = -2; y0 <=2; y0+=((double) 4)/(buffer->height-1)){
		for(double x0 = -2; x0 <=2; x0+=((double) 4)/(buffer->width-1)){
			double x = 0, y = 0, xtemp = 0;
			int iter = 0;
			while(((x*x+y*y) <= 4) && iter < MAX_ITER){
				xtemp = x*x - y*y + x0;
				y = 2 * x * y + y0;
				x = xtemp;
				iter++;
			} // TODO add in options for different mapping patterns
			// output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start)
			// Buffer has x and y swapped because of the order used by ncurses. This was probably not the best decision but is too late to change now
			// buffer->buffer[(int)(((y0+2)/4)*buffer->width + ((x0+2)/4)*buffer->width)] = iter%len;
			buffer->buffer[i] = iter%len;
			i++;
		}
	}
	draw_buffer(win, buffer, symbols);
	wrefresh(win);
	while(getch()!='q');
	free_buffer(buffer);
}
