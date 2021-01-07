// Hoy comemos mejillones - Reto 502
// https://www.aceptaelreto.com/problem/statement.php?id=502

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Obtener un puntero al primer elemento de la secuencia
int *corte(char *entrada, unsigned tam)
{
    // Array de los numeros que deseamos obtener de la 'entrada'
    int *numeros = (int *) malloc(sizeof(*numeros) * tam);
    int inumeros = 0; // Indice del array de numeros

    int iparte = 0; // Indice de la parte que se esta obteniendo
    char *sub_parte = (char *) malloc(sizeof(*sub_parte)); // Obtiene la cadena que se encuentra antes de llegar al espacio

    char *i = entrada;
    while (*i != '\0')
    {
        if (*i != ' ')
        {
            // Se convierte el caracter (*i = '2') a cadena ("2")
            char cad[sizeof(char *)]; // 8 por que un (char *) en mi pc tiene ese tamanio
            sprintf(cad, "%c", *i);
            strcat(sub_parte, cad);
            iparte++;
            sub_parte = (char *) realloc(sub_parte, sizeof(sub_parte) * iparte);             
        }
        if (*i == ' ')
        {
            numeros[inumeros++] = atoi(sub_parte);
            iparte = 0;
            free(sub_parte);
            sub_parte = (char *) malloc(sizeof(*sub_parte));
        }
        i++;
        if (*i == '\0')
        {
            numeros[inumeros] = atoi(sub_parte);
            iparte = 0;
            free(sub_parte);
            sub_parte = (char *) malloc(sizeof(*sub_parte));
        }
    }
    return numeros;
}


int main()
{
    char entrada[2048];
    char salto;
    int mejis; // Numero de mejillones
    int *tams;

    // Entrada
    scanf("%d", &mejis);
    scanf("%c", &salto);
    fgets(entrada, sizeof(entrada), stdin);

    tams = corte(entrada, mejis);

    int montones = 0;
    int actual; // Tamanio actual que poseemos para hacer el monton

    actual = tams[0];
    for (int i = 0; i < mejis; i++)
    {
        // Si el actual es menor o igual al mayor que tenemos se hace otro monton
        if (actual <= tams[i])
        {
            montones++;
            actual = tams[i];
        }
    }
    printf("%d\n", montones);
}
