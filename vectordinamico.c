#include <stdio.h>
#include <stdlib.h>

typedef int TELEMENTO;

/*Se vuelve a definir el tipo de datos que contiene el vector*/

typedef struct {
    TELEMENTO *datos; /*valores del vector*/
    int tam; /*tamano del vector*/
} STVECTOR; /*definición de la estructura*/

typedef STVECTOR *vectorP; /*puntero a estructura*/

/* Prototipos de las funciones */
void crear(vectorP *v1, int tam1);
void asignar(vectorP *v1, int posicion, TELEMENTO valor);
void tamano(vectorP v1, int *t);
void recuperar(vectorP v1, int pos, TELEMENTO *d);
void liberar(vectorP *v1);
void swap (vectorP *pvector,int m, int n);

/*Función crear: asigna memoria y devuelve la asignación al vector*/
void crear(vectorP *v1, int tam1) {
    int i = 0;
            
    *v1 = (vectorP) malloc(sizeof (STVECTOR));
    (*v1)->datos = (TELEMENTO*) malloc(tam1 * sizeof (TELEMENTO));
    (*v1)->tam = tam1;
    for (i = 0; i < tam1; i++)
        *((*v1)->datos + i) = 0; /*Inicializaci�n a 0 de las componentes del vector*/
}

/*Función asignar: Asigna un valor a una posición del vector */
void asignar(vectorP *v1, int posicion, TELEMENTO valor) {
    if(v1 != NULL && (*v1)->datos != NULL) //comprobase si existe o TAD e o vector
        *((*v1)->datos + posicion) = valor;
}

/*Función tamano: Devuelve el tamaño del vector*/
void tamano(vectorP v1, int *t) {
    if(v1 != NULL) //comprobase si existe o vector
        *t = v1->tam;
    else
        *t=-1;
    /* asignase -1 para indicar que non esta creado 
       o vector, polo que non se pode obter o tamaño */
}

/*Función recuperar: devuelve el valor de la posicion indicada del vector*/
void recuperar(vectorP v1, int pos, TELEMENTO *d) {
    /* Comprobase o vector existe e si se accede a unha posicion de memoria
       dentro das reservadas para o vector */
    if(v1 != NULL && pos >= 0 && pos < v1->tam)    
        *d = *((v1->datos) + pos);
}

/*Función liberar: libera la memoria asignada al TAD*/
void liberar(vectorP *v1) {
    if (v1 != NULL) {
        free((*v1)->datos);
        free(*v1);
    }
}

/*Funcion swap: intercambia el valor de dos posiciones del vector*/
void swap (vectorP *pvector,int m, int n){
    TELEMENTO aux,aux2;
    
    recuperar(*pvector,m,&aux);
    recuperar(*pvector,n,&aux2);
    asignar(pvector,m,aux2);
    asignar(pvector,n,aux);
    
}