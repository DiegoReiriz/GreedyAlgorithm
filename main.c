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
int cambio(int x, vectorP valor, vectorP *solucion, vectorP* stock);
void escribirMonedas();
int cargarMonedas(Moneda moneda[10]);

int main(int argc, char** argv) {
    
    int cantidad,pos,numMonedas;
    char opt, inf;
    
    Moneda moneda[10];
    
    cantidad=cargarMonedas(moneda);
    
    vectorP solucion = NULL,stock=NULL;

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

                do {
                    printf("\nSeleccionar Tipo de Moneda");
                    printf("\n==========================");
                    
                    for(pos=0;pos<cantidad;pos++){
                        printf("\n%d)%s",pos+1,moneda[pos].nombre);
                    }
                    
                    printf("\n0)Salir");
                    
                    do{
                        printf("\nOpcion: ");
                        scanf(" %d", &opt); //corregir fallo no menu

                    }while(opt<0 || opt>(cantidad+1));
                    
                    while ( opt != 0 && 0 != (numMonedas = solicitarMonedas())){
                        
                        cambio(numMonedas,moneda[pos].caras , &solucion, NULL);
                        imprimirVector(moneda[opt-1].caras);
                        imprimirVector(solucion);
                        if (!inf){
                            printf("\nStock Restante:");
                            imprimirVector(stock);
                        }
                    }
                } while (opt != 0);

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
int cambio(int x, vectorP valor, vectorP *solucion, vectorP* stock) {
    int len, val, i, suma = 0;
    TELEMENTO temp;
    
    tamano(valor,&len);
    crear(solucion,len);
    
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
    if (suma == x) {
        return 1;
    }else {
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

int cargarMonedas(Moneda moneda[10]){
    FILE *fp;
    int end,size,i,aux,cantidad;
    char *linea,*nombre,*valor;
    char buffer[LONG_MAX_LINE];
    char *separador=",";
    
    cantidad=0;
    
    if((fp=fopen("monedas.txt","r")) != NULL){
        do{   
            
            TCOLA temp;
            ColaVacia(&temp);
            
            linea=fgets(buffer,LONG_MAX_LINE,fp);
             
            nombre = strtok( linea, separador );    // Primera llamada => Primer token
                
            strcpy(moneda[cantidad].nombre,nombre);
            
            end=0;
            while( (valor = strtok( NULL, separador )) != NULL ){    // Posteriores llamadas
                AnadirCola(&temp, strtol(valor,NULL,10));             
                end++;
            }
            
            vectorP caras;
            crear(&caras,end);
            
            for(i=0;i<end;i++){
                PrimeroCola(temp,&aux);
                asignar(&caras,i,aux);
                EliminarCola(&temp);
            }
            moneda[cantidad].caras=caras;
            cantidad++;
        }while(!feof(fp));
    }else{
        
    }
    return cantidad;
}