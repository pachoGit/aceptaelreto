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

int comparar(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
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

    // Lista de montones que tenemos, ordenados ascendentemente
    int *montones = NULL;
    int imonton = 0;
    int i, j;

    // Guardamos el primer numero, ya que si o si se tiene un monton
    montones = (int *) malloc(sizeof(int));
    montones[imonton++] = tams[0];

    // Por cada mejillon que llega
    for (i = 1; i < mejis; i++)
    {
        // Ordenamos el array de montones en forma ascendente, porque
        // el proximo valor entrar debe caber en el menor valor posible
        // Donde se estea haciendo un monton
        qsort(montones, imonton, sizeof(int), comparar);

        int agregar = 1;
        for (j = 0; j < imonton; j++)
        {
            // Si el mejillon cabe en el monton actual, reemplazar el valor de ese
            // monton con el valor del mejillon, ya que eso sucede si se coloca encima
            // del mejillon :D
            if (montones[j] > tams[i])
            {
                montones[j] = tams[i];
                agregar = 0;
                break;
            }
        }
        // Si no se encuentra espacio para el nuevo valor, se
        // Agrega al array de montones para formar su propio monton
        if (agregar == 1)
        {
            montones = (int *) realloc(montones, sizeof(montones) * imonton);
            montones[imonton++] = tams[i];
        }
    }

    printf("%d\n", imonton);
    
    return 0;
}
