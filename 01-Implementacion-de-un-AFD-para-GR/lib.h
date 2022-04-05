#ifndef NUESTRA_LIB_
#define NUESTRA_LIB_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void obtenerToken(FILE*, char[]);
void limpiarBuffer(char cadena[]);
int procesarToken(char*);
char* tipoDeToken (int);
int grupoCaracter(char caracter);
void imprimirCadena(FILE*, char*, char*);
FILE *abrirArchivo (const char*, const char*);


#endif  // NUESTRA_LIB_
