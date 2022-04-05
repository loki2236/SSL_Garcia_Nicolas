#include "lib.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
    char nombreArchivoEntrada[] = "entrada.txt";
    char nombreArchivoSalida[] = "salida.txt";
    int tipoToken;
 
    // Abro archivos
    FILE*archivoEntrada= abrirArchivo(nombreArchivoEntrada, "r+");
    FILE*archivoSalida= abrirArchivo(nombreArchivoSalida, "w+");

    // Cadenas en la que voy leyendo
    char cadena[50];

    limpiarBuffer(cadena);
    
    if(feof(archivoEntrada)){
        printf("Archivo ingresado esta vacio \n");
    }    
    // Recorro ArchprocesarTokenarCadena(archivoEntrada, &cadena);
    while( !feof(archivoEntrada) ){
        // Lee un Token del archivo
        obtenerToken(archivoEntrada, cadena);

        if(strlen(cadena) > 0 ){
            printf("Token encontrado: %s - Largo: %d\n",cadena, strlen(cadena));
            printf("------------\n");
            tipoToken = procesarToken(cadena);
            char *tipoCadena = tipoDeToken(tipoToken);
            imprimirCadena(archivoSalida, cadena, tipoCadena);
            
            //Libero la memoria usada por el puntero
            free(tipoCadena);
        }
        limpiarBuffer(cadena);
    }

    // Cierro archivos
    fclose(archivoEntrada);
    fclose(archivoSalida);

    return 0;
}
