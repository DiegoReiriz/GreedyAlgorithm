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
    
    do{
        printf("\nModo de Operacion");
        printf("\n===================");
        printf("\n1)Monedas Infinitas");
        printf("\n2)Monedas Limitadas");
        printf("\n0)Salir");
        printf("\nOpcion: ");
        scanf("%c",&opt);//corregir fallo no menu
        
        switch(opt){
            case '1'://Monedas Infinitas
                
                break;
            case '2'://Monedas Limitadas
                
                break;
            default:
                printf("\nOpcion Erronea");
                break;
        }
        
    }while(opt != '0');
    
    return(EXIT_SUCCESS);
}

/** SOLICITAR MONEDAS
 * Solicita un numero de monedas por pantalla
 * 
 * @params none
 * 
 * @return int - numero de monedas
 */
int solicitarMonedas(){
    int monedas;
    printf("\nIntroduzca o numero de monedas do que quere cambio: ");
    scanf("%d",&monedas);
    return monedas;
}