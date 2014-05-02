/* 
 * File:   main.c
 * Author: entakitos
 *
 * Created on 2 de mayo de 2014, 20:19
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {

    char opt;
    short mode; //variable que indica en que modo se esta traballando

    do {
        printf("\nModo de Operacion");
        printf("\n===================");
        printf("\n1)Monedas Infinitas");
        printf("\n2)Monedas Limitadas");
        printf("\n0)Salir");
        printf("\nOpcion: ");
        scanf(" %c", &opt); //corregir fallo no menu
        getchar();

        switch (opt) {
            case '1'://Monedas Infinitas
                solicitarMonedas();
                break;
            case '2'://Monedas Limitadas
                solicitarMonedas();
                break;
            case '0':
                printf("\nFin del Prograna");
                break;
            default:
                printf("\nOpcion Erronea");
                break;
        }

    } while (opt != '0');

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

/** cambio
 * algoritmo voraz para dar o cambio
 * 
 * @param int - cantidad a devolver
 * @param vectorP - valor das monedas
 * @param vectorP - vector que almacena a cantidad de monedas que se devolve de cada tipo
 * 
 * @return Devolve un 1 si se dou a volta correctamente ou un 0
 * si se devolve un vector vacio.
 * 
 */
int cambio(int x, int valor[n], int solucion[n]) {
    for (int i = 0; i < n; i++) solucion[i] = 0;
    int i = 0, suma = 0;
    while (suma < x && i < n)
        if (suma + valor[i] <= x) {
            solucion[i]++;
            suma += valor[i];
        } else
            i++;
    if (suma == x) return 1;
    else {
        for (int i = 0; i < n; i++) solucion[i] = 0;
        return 0;
    }
}