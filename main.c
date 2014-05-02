/* 
 * File:   main.c
 * Author: entakitos
 *
 * Created on 28 de abril de 2014, 17:57
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {

    char opt;

    do {
        printf("MENU");
        printf("====");
        printf("1)Monedas ilimitadas");
        printf("2)Monedas limitadas");
        printf("1)Salir");
        scanf(" %c ", &opt);

        switch (opt) {
            case '1':

                break;
            case '2':

                break;

            default:

                break;
        }

    } while (opt != '0');

    return (EXIT_SUCCESS);
}

void cambio(int x, vectorP *vals, vectorP *res) {
    short size,aux;
    tamano(&res,&size);
    
    for (int i = 0; i < size; i++) asignar(res,i,0);
    int i = 0, suma = 0;
    while (suma < x && i < size){
        recuperar(&vals,i,&aux);
        if(suma + aux <= x){
            recuperar(&res,i,&aux);
            asignar(res,i,aux++);
            suma += aux++;
        }
        else
            i++;
    }
    if (suma == x) return 1;
    else {
        for (int i = 0; i < size; i++) asignar(res,i,0);
        return 0;
    }
}

