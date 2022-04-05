#include "lib.h"
#include <string.h>
#include <stdlib.h>

void limpiarBuffer(char cadena[]){
    memset(cadena, 0,50);
}

void obtenerToken(FILE* fileName, char cadena[]){
    char c; 
    int i = 0;
    fread(&c,sizeof(char),1,fileName);

    while(c!=','){
        cadena[i] = c;
        i++;
        fread(&c,sizeof(char),1,fileName);
        if(feof(fileName)){
           return;
        }
    }
}
/*int procesarToken(FILE*, char[]);
void imprimirCadena(FILE*, char[], int);*/

/**
 * Clasifica el Token segun la matriz de transicion dada
 * @author Nicolas Garcia
 * @param cadena Token a clasificar
 * @return Entero correspondiente al estado en la matriz de transicion \n
 * 1 = Octal / \n
 * 2 = Decimal / \n 
 * 3 = (Seria los correspondientes a 0x Error?) / \n
 * 4 = Hexadecimal / \n 
 * 5 = Octal / \n 
 * 6 = Error / \n 
 * @see "grupoCaracter"
 */
int procesarToken (char *cadena){
    //Estado 0 = Estado Inicial
    int estado = 0;
    //La matriz: 7 x 6
    int matriz[7][6] = {{1,2,2,6,6,6},{5,5,6,6,3,6},{2,2,2,6,6,6},{4,4,4,4,6,6},{4,4,4,4,6,6},{5,5,6,6,6,6},{6,6,6,6,6,6}};
    for(int i=0;i<strlen(cadena);i++){
        estado=matriz[estado][grupoCaracter(cadena[i])];
        // Estado de error para evitar que siga procesando.
        // Solo para ahorrar tiempo en tokens largos
        if (estado ==  6){
            break;
        }
    }

    return estado;
}

/**
 * Funcion Auxiliar: Clasifica el tipo de Token segun la matriz de transicion dada en el ejercicio
 * @author Nicolas Garcia
 * @param tipoToken Token a clasificar
 * @return Cadena correspondiente al estado en la matriz de transicion \n
 * (Recordar hacer FREE del parametro retornado)
 */
char* tipoDeToken (int tipoToken){
    char *cadena = malloc(14);
    switch(tipoToken){
        case 1:
        strcpy(cadena, "OCTAL");
        break;
        case 2:
        strcpy(cadena, "DECIMAL");
        break;
        case 3:
        strcpy(cadena, "NO RECONOCIDA");
        break;
        case 4:
        strcpy(cadena, "HEXADECIMAL");
        break;
        case 5:
        strcpy(cadena, "OCTAL");
        break;
        default:
        strcpy(cadena, "NO RECONOCIDA");
        break;
    }
    return cadena;
}

/**
 * Funcion Auxiliar que clasifica el caracter segun la columna correspondiente de la matriz de transicion
 *  
 * @param caracter Caracter a clasificar
 * @return Entero correspondiente a la columna en la matriz de transicion
 * @author Nicolas Garcia
 */
int grupoCaracter(char caracter){
    if(caracter == '0'){
        return 0;
    }else{
        if (caracter >= '1' && caracter <= '7'){
            return 1;
        }
        else{
            if (caracter >= '8' && caracter <='9'){
                return 2;
            }
            else{
                if((caracter >= 'a' && caracter<='f') || (caracter >= 'A' && caracter<='F')){
                    return 3;
                }
                else{
                    if (caracter == 'x' || caracter == 'X'){
                        return 4;
                    }
                }
            }
        }
    }
    return 5; //Error  
}

//Todo: Descripcion
void imprimirCadena(FILE* archivo, char *cadena, char* tipoToken){
    fprintf(archivo, "%-20s\t\t\t%s\n",cadena,tipoToken);
}

//Abro un archivo 
FILE *abrirArchivo (const char*nombreArchivo, const char*modoApertura) {
    FILE* fp = fopen(nombreArchivo, modoApertura);
     return fp;
	}
