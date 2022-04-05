#include "lib.h"
#include <stdio.h>

int main(void){
    
    char s[TAM];
    int estado_final;

    //Leer una cadena de caracteres
    ingresarCadena(s);
    //Repetir
    while (strlen(s) > 0){
    
        //Eliminar los espacios en blanco de la cadena
        myTrimm(s);

    //Eliminar los espacios en blanco de la cadena
    printf("Ejemplo para probar Trimm: \n"); //Solo a modo de prueba, cuando este listo todo esto se saca
    char cadena[]="\t  (2 + 4)+ 86 - 2 /     (10 + 6) = \t\t\n\n";
    printf("%s",cadena);
    myTrim(cadena);
    printf("Nueva cadena:\n%s\n",cadena);

        estado_final = procesarToken(s);
        if(estado_final == 1 || estado_final == 2){
            printf("Cadena reconocida correctamente, estado final: %d\n", estado_final);
        }else{
            printf("Cadena NO reconocida, estado final: %d\n", estado_final);
        }

        limpiarBuffer(s);
        ingresarCadena(s);
    }
 
    return 0;
}
