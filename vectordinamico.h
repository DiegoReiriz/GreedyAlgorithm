/*Tipo de datos de los elementos del vector*/
typedef int TELEMENTO;

/*tipo opaco, los detalles de implementaci�n est�n ocultos al usuario*/
typedef void * vectorP; 

/*Funci�n crear: asigna memoria y devuelve la asignaci�n al vector. Recibe v1 por referencia para devolver al programa principal la direcci�n de memoria reservada por este procedimiento*/
void crear(vectorP *v1,int tam1);

/*Funci�n asignar: Llena una posici�n del vector con un valor. Recibe una copia de la direcci�n de memoria reservada para el vector v1*/
void asignar(vectorP *v1,int posicion, TELEMENTO valor);

/*Función tamano: Devuelve el tamaño del vector*/
void tamano(vectorP v1,int *t);

/*Función recuperar: devuelve el valor de la posicion indicada del vector*/
void recuperar(vectorP v1, int pos,TELEMENTO *d);

/*Función liberar: libera la memoria asignada al TAD*/
void liberar(vectorP *v1);
/*Funcion swap: intercambia el valor de dos posiciones del vector*/
void swap (vectorP *pvector,int m, int n);

