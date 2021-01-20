// Division euclidea - Reto 304
// https://www.aceptaelreto.com/problem/statistics.php?id=304
// Tiempo: 0.068 - Memoria: 1112 KiB

#include <stdio.h>

int calcular_residuo(int dividendo, int divisor, int cociente)
{
    return dividendo - (divisor * cociente);
}

int main()
{
    int ncasos;
    int dividendo;
    int divisor;
    int cociente;
    int residuo;
    int i;

    scanf("%d", &ncasos);


    for (i = 0; i < ncasos; i++)
    {
        scanf("%d %d", &dividendo, &divisor);

        // Excepciones
        if (dividendo == 0 && divisor != 0)
        {
            printf("0 0\n");
            continue;
        }
        if (divisor == 0)
        {
            printf("DIV0\n");
            continue;
        }

        // Dos tipos de casos a aplicar

        // A.1 Cuando el dividendo y el divisor son positivos
        // A.2 Cuando el divisor es negativo

        // B.1 Cuando el dividendo y el divisor son negativos
        // B.2 Cuando el dividendo es negativo

        cociente = (int) (dividendo / divisor);
        residuo = calcular_residuo(dividendo, divisor, cociente);

        // Para la primera forma se aplica la formula dividendo = divisor * cociente + residuo
        if (dividendo > 0)
        {
            printf("%d %d\n", cociente, residuo);
        }

        // Para la segunda forma es algo complejo - Ejemplo: [(-14 / 2), (-14 / -2), (-14 / 3), (-14 / -3)]
        else
        {
            // Para las divisiones exactas
            if (residuo == 0)
            {
                printf("%d %d\n", cociente, residuo);
                continue;
            }

            // El cociente siempre es negativo - Ejemplo: -15 / 4
            if (divisor > 0)
            {
                // Al ser el cociente negativo tenemos que sumarle un -1 para llegar a la respuesta
                // por ejemplo: -14 / 3, al realizar la divison con (/) nos daria -4 y como residuo
                // -2, pero el residuo no puede ser negativo por que el cociente no seria -4 sino -5
                // de esa manera 3 * -5 = -15 y al sumar el residuo 1 <--> -15 + 1 nos da el dividendo -14
                cociente += -1; 
            }
            else // Ejemplo: -15 / -4 <--> -15 / -3
            {
                // Misma idea que la de arriba
                cociente += 1;
            }
            residuo = calcular_residuo(dividendo, divisor, cociente);
            printf("%d %d\n", cociente, residuo);
        }
    
    }

    return 0;
}
