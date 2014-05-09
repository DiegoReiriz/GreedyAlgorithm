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
    

int main(int argc, char** argv) {
escribirMonedas();
leerMonedas();

    char opt,inf;
    
    char monedas[3][6]={"euro","dolar","yen"};
    char monActual;
    
    short mode; //variable que indica en que modo se esta traballando

    /*
     * Asignacion temporal de monedas
     */
    vectorP euros,stockEuros,dolares,sotckDolares,yen,stockYens, solucion;
    crear(&euros, 8);
    crear(&solucion, 8);
    asignar(&euros, 0, 200);
    asignar(&euros, 1, 100);
    asignar(&euros, 2, 50);
    asignar(&euros, 3, 20);
    asignar(&euros, 4, 10);
    asignar(&euros, 5, 5);
    asignar(&euros, 6, 2);
    asignar(&euros, 7, 1);
    do {
        printf("\nModo de Operacion");
        printf("\n===================");
        printf("\n1)Monedas Infinitas");
        printf("\n2)Monedas Limitadas");
        printf("\n0)Salir");
        printf("\nOpcion: ");
        scanf(" %c", &opt); //corregir fallo no menu
        getchar();

        inf=0;//por defecto non se activa o modo infinito salvo que se seleccione no menu
        switch (opt) {
            case '1'://Monedas Infinitas
                inf=1;
                
            case '2'://Monedas Limitadas
                
                if(!inf){
                    
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

                    monActual=( sizeof(monedas) / sizeof(char) ) / (sizeof(monedas[0]) / sizeof(char) );//variable que gestiona que elemento do array que maneja os tipos de mona estamos usando
                    
                    switch (opt) {
                        case '1':
                            monActual--;
                            
                        case '2':
                            monActual--;
                            
                        case '3':
                            monActual--;
                            
                            printf("\nMoneda Seleccionada: %s \n",monedas[monActual]);
                            
                            cambioInf(solicitarMonedas(), euros, &solucion);
                            imprimirVector(solucion);
                            break;
                        default:

                            break;
                    }

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

    liberar(&euros);
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
        printf("%d \t",aux);
    }
}

void escribirMonedas(){
    FILE *fp;
    fp=fopen("monedas.txt","w");
    
    fprintf(fp,"euro 8");
    fprintf(fp,"\n200 0");
    fprintf(fp,"\n100 0");
    fprintf(fp,"\n50 0");
    fprintf(fp,"\n25 0");
    fprintf(fp,"\n10 0");
    fprintf(fp,"\n5 0");
    fprintf(fp,"\n2 0");
    fprintf(fp,"\n1 0");
    fprintf(fp,"\n");
    fprintf(fp,"\ndolar 4");
    fprintf(fp,"\n25 0");
    fprintf(fp,"\n10 0");
    fprintf(fp,"\n5 0");
    fprintf(fp,"\n1 0");
    fprintf(fp,"\n");
    fprintf(fp,"\nyen 6");
    fprintf(fp,"\n500 0");
    fprintf(fp,"\n100 0");
    fprintf(fp,"\n50 0");
    fprintf(fp,"\n10 0");
    fprintf(fp,"\n5 0");
    fprintf(fp,"\n1 0");
    fclose(fp);
    
}
void leerMonedas(){
    FILE *fp;
    int aux,aux3;
    char aux2[10];
    
    fp=fopen("monedas.txt","r");
    
    do{
        aux=fscanf(fp,"%s %d",&aux2,&aux3);
    }while(aux!= EOF);
    
    fclose(fp);
}
