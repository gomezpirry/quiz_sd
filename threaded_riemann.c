#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "function.h"
#include <pthread.h>
#include <time.h>

#include "util.h"

//This constants are defined in  util.h
//#define NUMWORKERS 5
//#define MAXRECT 10000

double widthbase;
int rectxworker;
double private_resultado[NUMWORKERS];
pthread_mutex_t mutex;
double total;

void* suma(void* idt) {
	int id = (int)idt;
	double base = (double)(rectxworker*id*widthbase); 
   // printf("\t\tId: %d base: %lf\n",id,base);
	for (int i = 0; i < rectxworker; i++)
		 private_resultado[id] += function(base + i*widthbase) * widthbase;
    
    pthread_mutex_lock(&mutex);
    total = total + private_resultado[id] ;
    pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, char** argv) {
	int low = 0;
	int high = 1;
    clock_t t1, t2;
	int j;
    pthread_t tid[NUMWORKERS];

	widthbase = (double)(high - low)/(double)MAXRECT;
	printf("Width of the base %lf\n\n",widthbase);
	printf("Number of workers %d\n", NUMWORKERS);
	rectxworker = (int)(MAXRECT/NUMWORKERS);
	printf("\tRectangles per worker %d\n",rectxworker);

    t1 = clock();
	for (j = 0; j < NUMWORKERS; j++)
        pthread_create(&tid[j],NULL,&suma,(void*)j); 

    t2 = clock();
	printf("Elapsed time starting threads %f ms\n",elapsedtime(t1,t2));

    t1 = clock();
	for (int i = 0; i < NUMWORKERS; i++) {
		void *status;
		int rc;
		rc = pthread_join(tid[i], &status);
		if (rc) {
			printf("ERROR; retrun code from pthread_join() is %d\n", rc);
			exit(-1);
		} 
	}

	t2 = clock();
	printf("Elapsed time waiting for threads %f ms\n",elapsedtime(t1,t2));

	printf("\tTotal: %lf\n\n", total);
}
