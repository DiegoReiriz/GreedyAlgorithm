/* 
 * File:   main.c
 * Author: Diego Reiriz Cores
 *
 * Created on 2 de mayo de 2014, 20:19
 */

#include <stdio.h>
#include <stdlib.h>
#include "vectordinamico.h"

int solicitarMonedas();
void imprimirVector(vectorP vec);
int cambioInf(int x, vectorP valor, vectorP *solucion);
void escribirMonedas();
void leerMonedas();
void carasEuros(vectorP *eur);
void carasDolar(vectorP *dol);
void carasYen(vectorP *y);

int main(int argc, char** argv) {
    //escribirMonedas();
    //leerMonedas();

    char opt, inf;

    char monedas[3][6] = {"euro", "dolar", "yen"};
    char monActual;

    short mode; //variable que indica en que modo se esta traballando


    /*
     * Asignacion temporal de monedas
     */
    vectorP moneda = NULL, solucion = NULL;

    do {
        printf("\nModo de Operacion");
        printf("\n===================");
        printf("\n1)Monedas Infinitas");
        printf("\n2)Monedas Limitadas");
        printf("\n0)Salir");
        printf("\nOpcion: ");
        scanf(" %c", &opt); //corregir fallo no menu
        getchar();

        inf = 0; //por defecto non se activa o modo infinito salvo que se seleccione no menu
        switch (opt) {
            case '1'://Monedas Infinitas
                inf = 1;

            case '2'://Monedas Limitadas

                if (!inf) {

                }

                do {
                    printf("\nSeleccionar Tipo de Moneda");
                    printf("\n==========================");
                    printf("\n1)Euro");
                    printf("\n2)Dolar");
                    printf("\n3)Yen");
                    printf("\n0)Salir");
                    printf("\nOpcion: ");
                    scanf(" %c", &opt); //corregir fallo no menu
                    getchar();

                    monActual = (sizeof (monedas) / sizeof (char)) / (sizeof (monedas[0]) / sizeof (char)); //variable que gestiona que elemento do array que maneja os tipos de mona estamos usando

                    if (moneda != NULL)
                        liberar(&moneda);

                    if (solucion != NULL)
                        liberar(&solucion);

                    switch (opt) {
                        case '1'://euro
                            crear(&moneda, 8);
                            carasEuros(&moneda);
                            crear(&solucion, 8);
                            break;
                        case '2'://dolar
                            crear(&moneda, 4);
                            carasDolar(&moneda);
                            crear(&solucion, 4);
                            break;
                        case '3'://yen
                            crear(&moneda, 6);
                            carasYen(&moneda);
                            crear(&solucion, 6);
                            break;

                            //printf("\nMoneda Seleccionada: %s \n",monedas[monActual-strtol(opt,NULL,10)]);

                        default:

                            break;
                    }

                    cambioInf(solicitarMonedas(), moneda, &solucion);
                    imprimirVector(moneda);
                    imprimirVector(solucion);

                } while (opt != '0');

                opt = ' ';

                break;
            case '0':

                break;
            default:
                printf("\nOpcion Erronea");
                break;
        }

    } while (opt != '0');

    liberar(&moneda);
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
int cambioInf(int x, vectorP valor, vectorP *solucion) {
    int len, val, i, suma = 0;
    TELEMENTO temp;

    tamano(*solucion, &len);

    for (i = 0; i < len; i++)
        asignar(solucion, i, 0);

    i = 0;
    while (suma < x && i < len) {
        recuperar(valor, i, &val);
        if (suma + val <= x) {
            recuperar(*solucion, i, &temp);
            asignar(solucion, i, ++temp);
            suma += val;
        } else
            i++;
    }
    if (suma == x) return 1;
    else {
        for (i = 0; i < len; i++)
            asignar(solucion, i, 0);
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

void carasEuros(vectorP *eur) {
    asignar(eur, 0, 200);
    asignar(eur, 1, 100);
    asignar(eur, 2, 50);
    asignar(eur, 3, 20);
    asignar(eur, 4, 10);
    asignar(eur, 5, 5);
    asignar(eur, 6, 2);
    asignar(eur, 7, 1);
}

void carasDolar(vectorP *dol) {
    asignar(dol, 0, 25);
    asignar(dol, 1, 10);
    asignar(dol, 2, 5);
    asignar(dol, 3, 1);
}

void carasYen(vectorP *y) {
    asignar(y, 0, 500);
    asignar(y, 1, 100);
    asignar(y, 2, 50);
    asignar(y, 3, 10);
    asignar(y, 4, 5);
    asignar(y, 5, 1);
}

void escribirMonedas() {
    FILE *fp;
    fp = fopen("monedas.txt", "w");

    fprintf(fp, "euro 8");
    fprintf(fp, "\n200 0");
    fprintf(fp, "\n100 0");
    fprintf(fp, "\n50 0");
    fprintf(fp, "\n25 0");
    fprintf(fp, "\n10 0");
    fprintf(fp, "\n5 0");
    fprintf(fp, "\n2 0");
    fprintf(fp, "\n1 0");
    fprintf(fp, "\n");
    fprintf(fp, "\ndolar 4");
    fprintf(fp, "\n25 0");
    fprintf(fp, "\n10 0");
    fprintf(fp, "\n5 0");
    fprintf(fp, "\n1 0");
    fprintf(fp, "\n");
    fprintf(fp, "\nyen 6");
    fprintf(fp, "\n500 0");
    fprintf(fp, "\n100 0");
    fprintf(fp, "\n50 0");
    fprintf(fp, "\n10 0");
    fprintf(fp, "\n5 0");
    fprintf(fp, "\n1 0");
    fclose(fp);

}

void leerMonedas() {
    FILE *fp;
    vectorP vec, stock;
    int aux, caras, i;
    char nombre[10];

    fp = fopen("monedas.txt", "r");

    do {
        aux = fscanf(fp, "%s %d", &nombre, &caras);



        for (i = 0; i < caras; i++) {

        }

    } while (aux != EOF);

    fclose(fp);
}
