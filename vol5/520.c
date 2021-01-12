// ¿Donde esta la bolita? - Reto 520
// https://www.aceptaelreto.com/problem/statement.php?id=520
// Resultado: Aceptable - Tiempo: 0.164s - Memoria: 1772 KiB

#include <stdio.h>
#include <stdlib.h>

#define SI 1
#define NO 0

typedef unsigned short boleano;

typedef struct cubilete_t
{
    int pos; // Posicion del cubilete
    boleano tiene_bolita; // Aca esta la bolita?
} cubilete_t;

// Inicia los cubiletes
void iniciar(cubilete_t *c, int tam, int pos)
{
    int i;
    
    for (i = 0; i < tam; i++)
    {
        c[i].pos = i + 1;
        c[i].tiene_bolita = NO;
        if ((i+1) == pos)
            c[i].tiene_bolita = SI;
    }
}

/* // Ver el contenido de cada cubilete
void imprimir(cubilete_t *c, int tam)
{
    int i;
    
    for (i = 0; i < tam; i++)
    {
        printf("Posicion: %d\n", c[i].pos);
        printf("Bolita:   %d\n", c[i].tiene_bolita);
    }
}
*/

// Intercambiar los cubiletes
void cambiar(cubilete_t *c, int n, int pos1, int pos2)
{
    int i;
    int p1, p2;

    for (i = 0; i < n; i++)
    {
        if (c[i].pos == pos1)
            p1 = i;
        if (c[i].pos == pos2)
            p2 = i;
    }

    c[p1].pos = pos2;
    c[p2].pos = pos1;
}

int bolita(cubilete_t *c, int n)
{
    int i;
    
    for (i = 0; i < n; i++)
    {
        if (c[i].tiene_bolita == SI)
            return c[i].pos;
    }
}

int main()
{
    int ncubiletes; // Cantidad de cubiletes a usar
    int pos_bolita; // Posicion del cubilete que contiene la bolita


    while (SI)
    {

        scanf("%d %d", &ncubiletes, &pos_bolita);
        if (ncubiletes == 0 && pos_bolita == 0)
            break;

        cubilete_t cubiletes[ncubiletes];
        iniciar(cubiletes, ncubiletes, pos_bolita);

        int m1 = -1, m2 = -1;
        while (SI)
        {
            scanf("%d %d", &m1, &m2);
            if (m1 == 0 && m2 == 0)
                break;
            cambiar(cubiletes, ncubiletes, m1, m2);
        }
        //imprimir(cubiletes, ncubiletes);

        printf("%d\n", bolita(cubiletes, ncubiletes));

    }
    
    return 0;
}
