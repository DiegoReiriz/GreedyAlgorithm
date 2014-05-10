#include "vectordinamico.h"

typedef struct{
    char *nombre;
    vectorP caras;
    vectorP stock;
} Moneda;

char *getName(Moneda moneda){
    return moneda.nombre;
}

void setName(Moneda *moneda,char* nombre){
    moneda->nombre=nombre;
}

vectorP *getStock(Moneda moneda){
    return (moneda.stock);
}

void setStock(Moneda *moneda,vectorP stock){
    moneda->stock=stock;
}

vectorP *getCaras(Moneda moneda){
    return moneda.caras;
}

void setCaras(Moneda *moneda,vectorP caras){
    moneda->caras=caras;
}