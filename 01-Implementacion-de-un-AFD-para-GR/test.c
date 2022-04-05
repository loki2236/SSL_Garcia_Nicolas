#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int test_TipoDeToken(void);
int test_ProcesarToken(void);
int test_abrirArchivo(void);

int main(void){

    test_TipoDeToken();
    test_ProcesarToken();
    test_abrirArchivo();
    return 0;
}

int test_ProcesarToken(void)
{
    /** 1 = Octal /
    * 2 = Decimal /
    * 3 = (Seria los correspondientes a 0x Error?) /
    * 4 = Hexadecimal /
    * 5 = Octal /
    * 6 = Error /
    * */

    // Test a Octal string:
    printf("Testing an Octal Number: ");
    assert(procesarToken("0245") == 5);
    assert(procesarToken("0912") == 6);
    assert(procesarToken("0") == 1);
    assert(procesarToken("09999") == 6);
    assert(procesarToken("012345") == 5);
    printf("Passed\n");

    // Test a Decimal string:
    printf("Testing a Decimal Number: ");
    assert(procesarToken("0245") == 5);
    assert(procesarToken("1702") == 2);
    assert(procesarToken("12345") == 2);
    assert(procesarToken("05989") == 6);
    printf("Passed\n");

    // Test a 0xError string:
    printf("Testing a 0x plus an Incorrect Number: ");
    assert(procesarToken("0xfgop") == 6);
    assert(procesarToken("0xxxxx") == 6);
    assert(procesarToken("0xx675") == 6);
    printf("Passed\n");

    // Test a Hexa string:
    printf("Testing a Hexadecimal Number: ");
    assert(procesarToken("0Xx546") == 6);
    assert(procesarToken("0xAaBb56") == 4);
    assert(procesarToken("0X") == 3);
    assert(procesarToken("0x5A6F0") == 4);
    printf("Passed\n");

    // Test a Error string:
    printf("Testing a non Alpha numeric character: ");
    assert(procesarToken("??") == 6);
    assert(procesarToken("' '") == 6);
    assert(procesarToken("&&") == 6);
    assert(procesarToken("?¡+!") == 6);
    printf("Passed\n");

    return 0;
}

int test_TipoDeToken(void)
{
    /** 1 = Octal /
    * 2 = Decimal /
    * 3 = (Seria los correspondientes a 0x Error?) /
    * 4 = Hexadecimal /
    * 5 = Octal /
    * 6 = Error /
    * */
    
    printf("Testing different tokens types: ");
    assert(strcmp(tipoDeToken(1) , "OCTAL") == 0);
    assert(strcmp(tipoDeToken(2) , "DECIMAL") == 0);
    assert(strcmp(tipoDeToken(8) , "NO RECONOCIDA") == 0);
    assert(strcmp(tipoDeToken(85) , "NO RECONOCIDA") == 0);
    assert(strcmp(tipoDeToken(3) , "NO RECONOCIDA") == 0);
    printf("Passed\n");
    return 0;
}

int test_abrirArchivo (){
    printf ("Testeando abrir un archivo que no existe: ");
    assert (abrirArchivo ("hola.txt", "r")==NULL);
    printf("Passed\n");
    return 0;
}