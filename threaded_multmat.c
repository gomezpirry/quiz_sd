#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "util.h"

// Variable globales, matriz A, B y C; A * B = C. Las matrices son cuadradas
double A[DIM][DIM];
double B[DIM][DIM];
double C[DIM][DIM];

// Definicion de los prototipos de la funciones
void multFilaIColJ(int, int); // Esta funcion multiplica A[I,] * B[,J] = C[I,J]
void* multIJ(void* data);     // Funcion usada para crear un hilo que hara parte
                              // de la multiplicacion de matrices 

// Definicion de tipo de dato en el cual se establecen los limites de las
// filas a procesar por un hilo.
// Ejemplo, suponga que hay 4 hilos y DIM es 8 entonces
// Hilo 1:  low = 0, high = 2
// Hilo 2:  low = 2, high = 4
// Hilo 3:  low = 4, high = 6
// Hilo 4:  low = 6, high = 8
struct ij {
	int low;
	int high;
};

int main(int argc, char** argv) {
	int i, j;
	int numpart = DIM/NUMWORKERS; // numero de filas de A por hilo
	                              // define num de filas de A que le toca a 
                                      // cada hilo e.g. 2
	struct ij particion[NUMWORKERS]; // Este es un arreglo del tipo
                                         // struct ij que guardara que rango
                                         // de filas le toca a cada hilo
	pthread_t tid[NUMWORKERS]; // arreglo de identificadores de hilos
	clock_t t1, t2; // variables del tipo clock para tomar el tiempo

	// Inicializacion de matrices A y B
	t1 = clock();
#ifdef TEST
	inicializar1(&A[0][0],&B[0][0]);
#else
	inicializar2(&A[0][0],&B[0][0]);
#endif
	t2 = clock();
	printf("Elapsed time initializing matrices %f ms\n",elapsedtime(t1,t2));

	//Crear los hilos
	t1 = clock();
	for (i = 0; i < NUMWORKERS; i++) {
		// COMPLETAR
		particion[i].low = i * numpart ; // ???
		particion[i].high = (i+1) * numpart; // ??
		pthread_create(&tid[i],NULL,&multIJ,(void*)&particion[i]); // ??
	}
	t2 = clock();
	printf("Elapsed time starting threads %f ms\n",elapsedtime(t1,t2));

	// En espera que termine los hilos su ejecucion
	t1 = clock();
	// COMPLETAR pthread_join
	i = 0;
	// bucle usado para esperar por la terminacion de los hilos
	for (; i < NUMWORKERS; i++) {
		void *status;
		int rc;
		rc = pthread_join(tid[i], &status);
		if (rc) {
			printf("ERROR; retrun code from pthread_join() is %d\n", rc);
			exit(-1);
		} 
	}
	// Escriba el bloque de codigo para esperar por la terminacion de los
	// hilos
	t2 = clock();
	printf("Elapsed time waiting for threads %f ms\n",elapsedtime(t1,t2));
#ifdef TEST
	if (validar1(&C[0][0]) == 0)
		printf("OK!\n");
	else
		printf("FAIL!\n");
#else
	printf("%f\n",validar2(&C[0][0]));
#endif
	return 0;
}

// COMPLETAR la funcion que define el trabajo a realizar por cada hilo
void* multIJ(void* _data) {
	struct ij *data = (struct ij*)_data; // COMPLETAR, como se le asigna el valor a la 
                            // variable *data
	int i = 0, j = 0;
	for (i = data->low; i < data->high; i++)
		for (j = 0; j < DIM; j++)
			multFilaIColJ(i,j);
	return NULL;
}

void multFilaIColJ(int i, int j) {
	int k;
	C[i][j] = 0;
	for (k = 0; k < DIM; k++) 
		C[i][j] += A[i][k] * B[k][j];
}
