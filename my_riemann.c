#include <stdio.h>
#include <math.h>
#include "function.h"

#define NUMWORKERS 5
#define MAXRECT 100

double widthbase;
int rectxworker;

double suma(int id) {
	int i;
	double base = (double)(rectxworker*id*widthbase); 
	double resultado = 0;
	printf("\t\tId: %d base: %lf\n",id,base);
	for (i = 0; i < rectxworker; i++)
		 resultado += function(base + i*widthbase) * widthbase;
	return resultado;
}

int main(int argc, char** argv) {
	int maxrect = MAXRECT;
	int low = 0;
	int high = 1;
	int nw = NUMWORKERS;
	int j;
	double total = 0;

	widthbase = (double)(high - low)/(double)maxrect;
	printf("Width of the base %lf\n\n",widthbase);
	printf("Number of workers %d\n",nw);
	rectxworker = (int)(maxrect/nw);
	printf("\tRectangles per worker %d\n",rectxworker);
	for (j = 0; j < nw; j++) 
		total += suma(j);
	printf("\tTotal: %lf\n\n", total);
}
