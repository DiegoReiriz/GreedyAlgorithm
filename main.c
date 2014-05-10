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
int cambio(int x, vectorP valor, vectorP *solucion, vectorP* stock);
void escribirMonedas();
void leerCarasMoneda(char nombre[10],vectorP *caras);

int main(int argc, char** argv) {
    //escribirMonedas();
    //leerMonedas();

    int cantidad;
    char opt, inf;
    //char monedas[3][6] = {"euro", "dolar", "yen"};
    char monActual;

    /*
     * Asignacion temporal de monedas
     */
    vectorP moneda = NULL, solucion = NULL, stock = NULL;

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

                    //monActual = (sizeof (monedas) / sizeof (char)) / (sizeof (monedas[0]) / sizeof (char)); //variable que gestiona que elemento do array que maneja os tipos de mona estamos usando

                    if (moneda != NULL)
                        liberar(&moneda);

                    if (solucion != NULL)
                        liberar(&solucion);

                    if (stock != NULL)
                        liberar(&stock);

                    switch (opt) {
                        case '1'://euro
                            crear(&moneda, 8);
                            leerCarasMoneda("euro",&moneda);
                            crear(&solucion, 8);
                            if (!inf)
                                crear(&stock, 8);
                            
                            break;
                        case '2'://dolar
                            crear(&moneda, 4);
                            leerCarasMoneda("dolar",&moneda);
                            crear(&solucion, 4);
                            if (!inf)
                                crear(&stock, 4);
                            
                            break;
                        case '3'://yen
                            crear(&moneda, 6);
                            leerCarasMoneda("yen",&moneda);
                            crear(&solucion, 6);
                            if (!inf)
                                crear(&stock, 6);

                            break;

                            //printf("\nMoneda Seleccionada: %s \n",monedas[monActual-strtol(opt,NULL,10)]);

                        default:

                            break;
                    }

                    while (0 != (cantidad = solicitarMonedas()) && opt != '0') {
                        cambio(cantidad, moneda, &solucion, NULL);
                        imprimirVector(moneda);
                        imprimirVector(solucion);
                        if (!inf){
                            printf("\nStock Restante:");
                            imprimirVector(stock);
                        }
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

    if(moneda != NULL)
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
int cambio(int x, vectorP valor, vectorP *solucion, vectorP* stock) {
    int len, val, i, cant, suma = 0;
    TELEMENTO temp,temp2,size;
    vectorP stockTemp;
    
    tamano(stock,&size);
    tamano(*solucion, &len);
    crear(&stockTemp,temp);
    
    for (i = 0; i < len; i++)
        asignar(solucion, i, 0);

    i = 0;
    while (suma < x && i < len) {
        if (size != -1) {
            recuperar(stock, i, &cant);
            recuperar(stockTemp,i,&temp);
            if (cant-temp) {
                recuperar(valor, i, &val);
                if (suma + val <= x) {
                    recuperar(*solucion, i, &temp);
                    asignar(solucion, i, ++temp);
                    recuperar(stockTemp, i, &temp);
                    asignar(&stockTemp,i,++temp);
                    suma += val;
                } else
                    i++;
            }else
                i++;
        } else {
            recuperar(valor, i, &val);
            if (suma + val <= x) {
                recuperar(*solucion, i, &temp);
                asignar(solucion, i, ++temp);
                suma += val;
            } else
                i++;
        }

    }
    if (suma == x) {
        if (size != -1) {
            tamano(stock,&cant);

            for(i=0;i<=cant;i++){
                recuperar(stock, i, &temp);
                recuperar(stockTemp, i, &temp2);
                asignar(stock,i,temp-temp2);
            }
        }
        return 1;
    }else {
        for (i = 0; i < len; i++)
            asignar(solucion, i, 0);
        return 0;
    }
    if(stock != NULL)
        liberar(&stockTemp);
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

void leerCarasMoneda(char nombre[10],vectorP *caras){
    FILE *fp;
    vectorP vec[10], stock;
    TELEMENTO elem;
    int aux,i;
    char opt[5],nom[10],moneda[10];

    fp = fopen("monedas.txt", "r");

    do {
        
        aux = fscanf(fp, "%s %s", &opt,&nom);
        
        if(opt=="m:" && nom==nombre){
            aux = fscanf(fp, "%s %d", &opt,&elem);
            while(aux != EOF && opt == "c:"){
                i++;
                asignar(caras,i,elem);
                aux = fscanf(fp, "%s %d", &opt,&elem);
            }
        }
            
    }while(aux != EOF);

    fclose(fp);
}
