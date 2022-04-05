#include "lib.h"
#include <string.h>
#include <stdlib.h>

int ERROR_PILA=-1;

void limpiarBuffer(char cadena[]){
    memset(cadena, 0,strlen(cadena));
}

/**
 * Clasifica el Token segun la matriz de transicion dada
 * @author Nicolas Garcia
 * @param cadena Token a clasificar
 * @return Entero correspondiente al estado en la matriz de transicion 
 * @see "grupoCaracter"
 * 
 */
int procesarToken (char *cadena){
    //Estado 0 = Estado Inicial
    int estado = 0;
    int cima_pila = 0;
    int cima_pila_bool = 0;
    int grupo_caracter = 0;
    //La matriz: 2 x 4 x 6
    int matriz[2][4][6] = {
        //La 'primera' matriz son los estados siguientes si la pila esta vacia
        //La 'segunda' matriz son los estados siguientes si la pila NO esta vacia
        {{4,1,4,0,4,4},{1,1,0,4,4,4},{4,4,0,4,4,4},{4,4,4,4,4,4}},
        {{4,1,4,0,4,4},{1,1,0,4,2,4},{4,4,0,4,2,4},{4,4,4,4,4,4}}
    };
    // Creo el Stack
    struct Stack* stack = createStack(200);
    push(stack, '$');
    
    printf("Analizando cadena: %s \n", cadena);
    for(int i=0;i<strlen(cadena);i++){
        
        cima_pila = pop(stack);
        grupo_caracter = grupoCaracter(cadena[i]);
        
        //Bool
        cima_pila_bool = (cima_pila == '$') ? 0 : 1;

        estado=matriz[cima_pila_bool][estado][grupo_caracter];

        //Debug
        printf("Loop %d: cima_pila[%c] estado[%d] - Caracter [%c] - Grupo[%d]\n",i, cima_pila, estado, cadena[i], grupo_caracter);
        
        //Como detecto los casos en los que tengo que hacer un push extra?
        if(cima_pila == 'R'){
            if(grupo_caracter!=4)
            push(stack, 'R');
            //Extra si es un '('
            if(estado==0 && grupo_caracter == 3)
            push(stack, 'R');
        }else{
            //Asumo cima_pila == '$'
            push(stack, '$');
            if(estado==0 && grupo_caracter==3)
            push(stack, 'R');
        }
        
        // Estado de error para evitar que siga procesando.
        // Solo para ahorrar tiempo en tokens largos
        //TODO: Puedo identificar el caracter que causa error acá
        if (estado ==  4)
            break;
    }

    // No olvidarnos de esto.
    freeStack(stack);

    return estado;
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
        if (caracter >= '1' && caracter <= '9'){
            return 1;
        }
        else{
            if (caracter == '-' || caracter == '+'|| caracter == '*'|| caracter == '/'){
                return 2;
            }
            else{
                if(caracter == '('){
                    return 3;
                }
                else{
                    if (caracter == ')'){
                        return 4;
                    }
                }
            }
        }
    }
    return 5; //Error  
}


/**
 * Funcion Auxiliar que elimina los espacios blancos dentro de toda la cadena
 *  
 * @param cadena Caracter a modificar
 * @return Misma cadena sin los espacios en blanco
 * @author Matias Planchuelo
 */
void myTrim (char *cadena)
{
    int i=0;
    int largo = strlen(cadena);
    leftTrim (cadena); rightTrim(cadena);
    while (cadena[i] != '\0')
    {
        if (cadena[i] == ' ')
        {
            for (int j=i;j<largo;j++)
            {
                cadena[j]=cadena[j+1];
            }
        largo--;
        }
        if (cadena[i]!=' ')
        {
            i++;
        }
    }
    return;
}

void rightTrim (char *cadena)
{
    int largo = strlen (cadena) - 1;
    while (largo>0)
    {
        switch (cadena[largo])
        {
            case '\t':
            case '\n':
                cadena[largo] = '\0';
                largo--;
                break;

            default:
                return;
        }
    }
}

void leftTrim (char *cadena)
{
    reverse(cadena);
    rightTrim(cadena);
    reverse(cadena);
}

/**
 * Funcion Auxiliar que invierte el orden de toda la cadena
 *  
 * @param cadena Caracter a modificar
 * @return Misma cadena invertido su orden
 * @author Matias Planchuelo
 */
void reverse (char *cadena)
{
    int i, j;
    char *dup;
    dup=strdup(cadena);
    j=strlen(cadena) - 1;

    for (i=0;i<strlen(cadena);i++)
    {
        cadena[i]=dup[j];
        j--;
    }
    free(dup); 
}    


struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
 
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
 

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}
 

void push(struct Stack* stack, int item)
{
    if (isFull(stack)){
        printf("PILA LLENA");
        return;
    } 
    stack->array[++stack->top] = item;
    //printf("%d Aniadido a la pila\n", item);
}
 

int pop(struct Stack* stack)
{
    if (isEmpty(stack)){
        printf("PILA VACIA");
        return ERROR_PILA;
    } 
    return stack->array[stack->top--];
}

/**
 * Funcion Auxiliar que destruye el stack
 *  
 * @param stack Puntero al stack actual
 * @return 1
 * @author Nicolas Garcia
 */

int freeStack(struct Stack* stack){
    free(stack->array);
    free(stack);
    return 1;
}

void ingresarCadena(char cadena[]){
    printf("Ingrese una cadena (Enter para finalizar): ");
    fgets(cadena, TAM-1, stdin);
	cadena[strcspn(cadena, "\n")] = '\0';
}