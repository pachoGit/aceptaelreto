// Tension descompensada - Reto 506
// https://www.aceptaelreto.com/problem/statement.php?id=506
// Aceptado - Tiempo: 0.04s - Memoria: 1112 KiB

#include <stdio.h>

int main()
{
    int ncasos;
    int max, min;
    char barra; // Para la barra '/'

    scanf("%d", &ncasos);

    int i;
    for (i = 0; i < ncasos; i++)
    {
        scanf("%d %c %d", &max, &barra, &min);
        if (max >= min)
            printf("BIEN\n");
        else
            printf("MAL\n");
    }

    return 0;
}
