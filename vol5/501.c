// Batalla de dados - Reto 501
// https://www.aceptaelreto.com/problem/statement.php?id=501

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convertir un numero en formato char ('5') a entero (5)
#define a_ent(caracter) (caracter - '0')

// Guardar la informacion de la primera linea de la entrada
typedef struct Info
{
    int tropas_defensa;
    int tropas_ataque;
    int max_dados_defensa;
    int max_dados_ataque;
    int noleadas;
} Info;

Info info;

// Convierte la entrada en un array de numeros y devuelve un puntero al primer
// elemento, ademas retorna el tamanio del array a travez de la variable 'tam'
int *convertir_entrada(char *entrada, int *tam)
{
    int  *valores = (int *) malloc(sizeof(*valores));
    int i = 0;
    char *temp;

    for (temp = entrada; *temp != '\0'; temp++)
    {
        if (*temp == ' ')
            continue;
        valores[i++] = a_ent(*temp);
        valores = (int *) realloc(valores, sizeof(valores) * i);
    }
    *tam = i;
    return valores;
}

// Traer los movimientos de los participantes
int *traer_valores(int *array, int tam_array, int cantidad)
{
    int *temp = (int *) malloc(sizeof(int) * cantidad);
    int icantidad = 0;
    int i;
    
    for (i = 0; i < tam_array; i++)
    {
        if (array[i] == 0)
            continue;
        if (icantidad >= cantidad)
            break;
        temp[icantidad++] = array[i];
        array[i] = 0;
    }
    return temp;
}

// Para ordenar con qsort pero en forma descendente
int comparar(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

// Realiza el proceso principal de pelea entre los participantes
void pelear(int *defensa, int *ataque, int tam)
{
    int i;

    for (i = 0; i < tam; i++)
    {
        if (ataque[i] <= defensa[i])
            info.tropas_ataque--;
        else
            info.tropas_defensa--;
    }
}

int main()
{
    char entrada[2048]; // Alcanzara para las demas pruebas?
    char salto;
    scanf("%d %d %d %d %d", &info.tropas_defensa, &info.tropas_ataque, &info.max_dados_defensa,
          &info.max_dados_ataque, &info.noleadas);
    scanf("%c", &salto);
    fgets(entrada, sizeof(entrada), stdin);

    // Debido a que en la entrada los numeros son de un digito siempre, eso nos
    // facilita el parseo para obtener un array de numeros
    int nlanzamientos;
    int *lanzamientos = convertir_entrada(entrada, &nlanzamientos);
    
    // Cantidad de dados que le toca tirar a cada lado
    // Se debe usar la maxima cantidad de dados que se pueda
    int ndados_defensa;
    int ndados_ataque;
    
    int ioleadas; // Indice de la oleadas
    int *val_defensa; // Valores actuales de los dados de defensa
    int *val_ataque; // Valores actuales de los dados de ataque

    // Bucle principal
    for (ioleadas = 0; ioleadas < info.noleadas; ioleadas++)
    {
        // Cantidad de dados que le toca tirar a cada lado
        // Se debe usar la maxima cantidad de dados que se pueda
        ndados_defensa = (info.tropas_defensa < info.max_dados_defensa ? info.tropas_defensa : info.max_dados_defensa);
        ndados_ataque = (info.tropas_ataque < info.max_dados_ataque ? info.tropas_ataque : info.max_dados_ataque);

        // No voy a ir eliminando espacios del array mientras voy sacando los
        // lanzamientos de los dados, lo que hare sera colocar en cero los valores
        // ya obtenidos
        val_defensa = traer_valores(lanzamientos, nlanzamientos, ndados_defensa);
        val_ataque = traer_valores(lanzamientos, nlanzamientos, ndados_ataque);
        // Ordenamos en forma descendente
        qsort(val_defensa, ndados_defensa, sizeof(int), comparar);
        qsort(val_ataque, ndados_ataque, sizeof(int), comparar);

        // Pelear solo con el que tiene menor cantidad de dados, ya que lo que no tiene pareja
        // se descartan
        int p = (ndados_ataque < ndados_defensa ? ndados_ataque : ndados_defensa);
        pelear(val_defensa, val_ataque, p);
        free(val_defensa);
        free(val_ataque);
    }
    /*
    printf("Tropas de defensa: %d\n", info.tropas_defensa);
    printf("Tropas de ataque: %d\n", info.tropas_ataque);
    */
    printf("%d %d\n", info.tropas_defensa, info.tropas_ataque);

    return 0;
}
