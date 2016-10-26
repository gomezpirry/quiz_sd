#ifndef __UTILH__
#define __UTILH__

#define TEST

#ifdef TEST
#define DIM 10
#define NUMWORKERS 1000
#define MAXRECT 1000000
#else
#define DIM 1000
#define NUMWORKERS 1000
#define MAXRECT 100000
#endif

#ifdef TEST
// Esta funcion debe recibir las matrices A y B como argumentos
void inicializar1(double *, double*);

// Esta funcion debe recibir como argumento la variable C
// Devuelve un valor de 0 si todo esta bien, 1 de otra forma
int validar1(double*);

#else 
// Esta funcion debe recibir las matrices A y B como argumentos
void inicializar2(double *, double*);
// Esta funcion debe recibir como argumento la variable C
double validar2(double*);
#endif

#define elapsedtime(t1,t2) (((float)t2 - (float)t1) / 1000000.0F ) * 1000
void printMatrix(double*);


#endif
