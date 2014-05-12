/* 
 * File:   main.c
 * Author: Diego Reiriz Cores
 *
 * Created on 2 de mayo de 2014, 20:19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vectordinamico.h"
#include "colas.h"

#define LONG_MAX_LINE 500

typedef struct {
    char nombre[10];
    vectorP *caras;
    vectorP *stock;
} Moneda;


int solicitarMonedas();
void imprimirVector(vectorP vec);
int cambio(int x, vectorP valor, vectorP *solucion, vectorP *stock);
void escribirMonedas();
int cargarStock(Moneda moneda[10]);
void escribirStock(Moneda moneda[10], int cantidad);
void gestionarStock(Moneda *moneda);

int main(int argc, char** argv) {

    int cantidad, pos, numMonedas;
    char opt, inf, optInf;

    Moneda moneda[10];

    cantidad = cargarMonedas(moneda);

    vectorP solucion = NULL, stock = NULL;

    do {
        printf("\nModo de Operacion");
        printf("\n===================");
        printf("\n1)Monedas Infinitas");
        printf("\n2)Monedas Limitadas");
        printf("\n0)Salir");
        printf("\nOpcion: ");
        scanf(" %d", &opt); //corregir fallo no menu

        inf = 0; //por defecto non se activa o modo infinito salvo que se seleccione no menu
        switch (opt) {
            case 1://Monedas Infinitas
                inf = 1;

            case 2://Monedas Limitadas

                if (!inf) {
                    cargarStock(moneda);
                    imprimirVector(moneda[1].stock);
                }

                do {
                    printf("\nSeleccionar Tipo de Moneda");
                    printf("\n==========================");

                    for (pos = 0; pos < cantidad; pos++) {
                        printf("\n%d)%s", pos + 1, moneda[pos].nombre);
                    }

                    printf("\n0)Salir");

                    do {
                        printf("\nOpcion: ");
                        scanf(" %d", &opt); //corregir fallo no menu

                    } while (opt < 0 || opt > (cantidad + 1));

                    optInf = '1';
                    
                    if (!inf) {
                        printf("\nSelecciona unha opcion");
                        printf("\n======================");
                        printf("\n1)insertar  numero");
                        printf("\n2)aumentar stock");
                        do {
                            printf("\nOpcion: ");
                            scanf(" %c", &optInf); //corregir fallo no menu

                        } while (optInf < '1' || optInf > '2');

                        if (optInf == '2'){
                            gestionarStock(&moneda[opt - 1]);
                        }
                    }

                    while (optInf == '1' && opt != 0 && 0 != (numMonedas = solicitarMonedas())) {

                        if (cambio(numMonedas, moneda[opt - 1].caras, &solucion, (moneda[opt - 1].stock))) {
                            imprimirVector(moneda[opt - 1].caras);
                            imprimirVector(solucion);
                            if (!inf) {
                                printf("\nStock Restante:");
                                imprimirVector(moneda[opt - 1].stock);
                            }
                        } else {
                            printf("\nNon se pudo dar o cambio");
                        }
                    }

                } while (opt != 0);
                if (!inf) {
                    escribirStock(moneda, cantidad);
                }
                opt = -1;

                break;
            case 0:

                break;
            default:
                printf("\nOpcion Erronea");
                break;
        }

    } while (opt != 0);




    return (EXIT_SUCCESS);
}

/** SOLICITAR MONEDAS
 * Solicita un numero de monedas por pantalla
 * 
 * @params none
 * 
 * @return int - numero de monedas
 */
int solicitarMonedas() {
    int monedas;
    printf("\nIntroduzca o numero de monedas do que quere cambio: ");
    scanf(" %d", &monedas);
    return monedas;
}

/** cambioInf
 * algoritmo voraz para dar o cambio con monedas infinitas
 * 
 * @param int - cantidad a devolver
 * @param vectorP - valor das monedas
 * @param vectorP - vector que almacena a cantidad de monedas que se devolve de cada tipo
 * 
 * @return Devolve un 1 si se dou a volta correctamente ou un 0
 * si se devolve un vector vacio.
 * 
 */
int cambio(int x, vectorP valor, vectorP *solucion, vectorP *stock) {
    int len, val, i, cant, suma = 0;
    TELEMENTO temp, temp2;

    tamano(valor, &len);
    crear(solucion, len);

    vectorP stock2;
    crear(&stock2, len);

    for (i = 0; i < len; i++) {
        asignar(solucion, i, 0);
        asignar(&stock2, i, 0);
    }

    i = 0;
    while (suma < x && i < len) {
        if (stock == NULL) {
            recuperar(valor, i, &val);
            if (suma + val <= x) {
                recuperar(*solucion, i, &temp);
                asignar(solucion, i, ++temp);
                suma += val;
            } else
                i++;
        } else {
            recuperar(stock, i, &cant);
            recuperar(stock2, i, &temp);
            if (cant - temp > 0) {
                recuperar(valor, i, &val);
                if (suma + val <= x) {
                    recuperar(*solucion, i, &temp);
                    asignar(solucion, i, ++temp);
                    recuperar(stock2, i, &temp);
                    asignar(&stock2, i, ++temp);
                    suma += val;
                    cant--;
                } else
                    i++;
            } else
                i++;
        }
    }
    if (suma == x) {
        for (i = 0; i < len && stock != NULL; i++) {
            recuperar(stock2, i, &temp);
            recuperar(stock, i, &temp2);
            asignar((vectorP *) & stock, i, temp2 - temp);
        }

        liberar(&stock2);

        return 1;
    } else {
        for (i = 0; i < len; i++)
            asignar(solucion, i, 0);
        liberar(&stock2);
        return 0;
    }

}

/** imprimirVector
 * Funcion que se encargr de imprimir por pantalla o contenido do vector que se lle pasa como argumento
 * @param vectorP - vector a imprimir
 */
void imprimirVector(vectorP vec) {
    int len, i;
    TELEMENTO aux;

    tamano(vec, &len);

    printf("\n");
    for (i = 0; i < len; i++) {
        recuperar(vec, i, &aux);
        printf("%d \t", aux);
    }
}

int cargarMonedas(Moneda moneda[10]) {
    FILE *fp;
    int end, size, i, aux, cantidad;
    char *linea, *nombre, *valor;
    char buffer[LONG_MAX_LINE];
    char *separador = ",";

    cantidad = 0;

    if ((fp = fopen("monedas.txt", "r")) != NULL) {
        do {

            TCOLA temp;
            ColaVacia(&temp);

            linea = fgets(buffer, LONG_MAX_LINE, fp);

            nombre = strtok(linea, separador); // Primera llamada => Primer token

            strcpy(moneda[cantidad].nombre, nombre);

            end = 0;
            while ((valor = strtok(NULL, separador)) != NULL) { // Posteriores llamadas
                AnadirCola(&temp, strtol(valor, NULL, 10));
                end++;
            }

            vectorP caras;
            crear(&caras, end);

            for (i = 0; i < end; i++) {
                PrimeroCola(temp, &aux);
                asignar(&caras, i, aux);
                EliminarCola(&temp);
            }
            moneda[cantidad].caras = caras;
            moneda[cantidad].stock = NULL;
            cantidad++;
        } while (!feof(fp));
    } else {

    }
    fclose(fp);

    return cantidad;
}

int cargarStock(Moneda moneda[10]) {
    FILE *fp;
    int end, size, i, aux, cantidad;
    char *linea, *nombre, *valor;
    char buffer[LONG_MAX_LINE];
    char *separador = ",";

    cantidad = 0;

    if ((fp = fopen("stock.txt", "r")) != NULL) {
        do {

            TCOLA temp;
            ColaVacia(&temp);

            linea = fgets(buffer, LONG_MAX_LINE, fp);

            nombre = strtok(linea, separador); // Primera llamada => Primer token

            end = 0;
            while ((valor = strtok(NULL, separador)) != NULL) { // Posteriores llamadas
                AnadirCola(&temp, strtol(valor, NULL, 10));
                end++;
            }

            vectorP stock;
            crear(&stock, end);

            for (i = 0; i < end; i++) {
                PrimeroCola(temp, &aux);
                asignar(&stock, i, aux);
                EliminarCola(&temp);
            }
            moneda[cantidad].stock = stock;
            cantidad++;

        } while (!feof(fp));
    } else {

    }
    fclose(fp);
    return cantidad;
}

void escribirStock(Moneda moneda[10], int cantidad) {
    FILE *fp;
    TELEMENTO elem;
    int tam, i = 0, j = 0;

    if ((fp = fopen("stock.txt", "w+")) != NULL) {
        do {
            fprintf(fp, "%s", moneda[i].nombre);
            tamano(moneda[i].stock, &tam);
            for (j = 0; j < tam; j++) {
                recuperar(moneda[i].stock, j, &elem);
                fprintf(fp, ",%d", elem);
            }
            fprintf(fp, "\n");
            i++;
        } while (i <= cantidad);
    }
}

void gestionarStock(Moneda *moneda){
    vectorP stock=moneda->stock,caras=moneda->caras;
    int aux;
    
    tamano(stock,&aux);
    printf("\n%d",aux);
    tamano(caras,&aux);
    printf("\n%d",aux);

}