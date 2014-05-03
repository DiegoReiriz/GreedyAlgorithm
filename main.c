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
/*
 * 
 */
int main(int argc, char** argv) {

    char opt;
    short mode; //variable que indica en que modo se esta traballando

    /*
     * Asignacion temporal de monedas
     */
    vectorP monedas,solucion;
    crear(&monedas,8);
    crear(&solucion,8);
    asignar(&monedas,0,200);
    asignar(&monedas,1,100);
    asignar(&monedas,2,50);
    asignar(&monedas,3,20);
    asignar(&monedas,4,10);
    asignar(&monedas,5,5);
    asignar(&monedas,6,2);
    asignar(&monedas,7,1);

    
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
                cambioInf(solicitarMonedas(),monedas,&solucion);
                imprimirVector(solucion);
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

    liberar(&monedas);
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
    int len,val,i,suma=0;
    TELEMENTO temp;
    
    tamano(*solucion,&len);
    
    for (i = 0; i < len; i++) 
        asignar(solucion,i,0);
    
    i=0;
    while (suma < x && i < len){
        recuperar(valor,i,&val);
        if (suma + val <= x) {
            recuperar(*solucion,i,&temp);
            asignar(solucion,i,++temp);
            suma += val;
        } else
            i++;
    }
    if (suma == x) return 1;
    else {
        for (i = 0; i < len; i++) 
            asignar(solucion,i,0);
        return 0;
    }
}


void imprimirVector(vectorP vec){
    int len,i;
    TELEMENTO aux;
    
    tamano(vec,&len);
    
    printf("\n");
    for(i=0;i<len;i++){
        recuperar(vec,i,&aux);
    }
}