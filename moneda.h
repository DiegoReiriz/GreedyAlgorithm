#include "vectordinamico.h"

typedef void *Moneda;

char *getName(Moneda moneda);

void setName(Moneda *moneda,char* nombre);

vectorP *getStock(Moneda moneda);

void setStock(Moneda *moneda,vectorP stock);

vectorP *getCaras(Moneda moneda);

void setCaras(Moneda *moneda,vectorP caras);