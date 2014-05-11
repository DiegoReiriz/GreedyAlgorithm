#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vectordinamico.h"

typedef struct {
    char nombre[10];
    vectorP caras;
    vectorP stock;
} structMoneda;

typedef structMoneda *Moneda;

void crearMoneda(Moneda *moneda){
    *moneda=(structMoneda *) malloc(sizeof (structMoneda *));
}

char *getName(Moneda moneda) {
    return (*moneda).nombre;
}

void setName(Moneda *moneda, char* nombre) {
    strcpy((*moneda)->nombre,nombre);
}

vectorP *getStock(Moneda moneda) {
    return (*moneda).stock;
}

void setStock(Moneda *moneda, vectorP stock) {
    (*moneda)->stock = stock;
}

vectorP *getCaras(Moneda moneda) {
    return (*moneda).caras;
}

void setCaras(Moneda *moneda, vectorP caras) {
    (*moneda)->caras = caras;
}

void liberarMoneda(Moneda *moneda) {
    if ((*moneda)->caras != NULL) {
        liberar((*moneda)->caras);
        (*moneda)->caras = NULL;
    }
    if ((*moneda)->stock != NULL) {
        liberar((*moneda)->stock);
        (*moneda)->caras = NULL;
    }
}