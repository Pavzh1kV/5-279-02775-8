/* ******************************************** */
/* Задача о рюкзаке. Вирт-1, 182 с.  \ruczak2.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 10
typedef struct obj
{
    int w, v;
};
obj a[n];
int limw, totv, maxv, w1, w2, w3;
int s[n], opts[n];
static int K = 0;
/* =========================================== */
void tryy(obj a[n], int i, int tw, int av)
{
    int av1, tw1, j;
    K++;
    /* Попытка включения объекта i */
    tw1 = tw + a[i].w;
    if (tw + a[i].w <= limw)
    {
        s[i] = i + 1;
        if (i < n - 1)
            tryy(a, i + 1, tw1, av);
        else if (av > maxv)
        {
            maxv = av;
            for (j = 0; j < n; j++)
                opts[j] = s[j];
        }
        s[i] = 0;
    }
    /* Попытка исключения объекта i */
    av1 = av - a[i].v;
    if (av1 > maxv)
        if (i < n - 1)
            tryy(a, i + 1, tw, av1);
        else
        {
            maxv = av1;
            for (j = 0; j < n; j++)
                opts[j] = s[j];
        }
}

/* ============================================== */
main()
{
    /*  obj a[n]; *//* можно и здесь определить, работает верно */
    /* Вес и стоимость предметов можно вводить по запросу или
    	инициализировать */
    setlocale(LC_ALL,"Russian");
    obj a[n] =
    {
        10, 18, 11, 20, 12, 17, 13, 19, 14, 25, 15, 21, 16, 27, 17, 23,
        18, 25,
        19, 24
    };
    int ss;
    int i, w, v;
    totv = 0;
    for (i = 0; i < n; i++)
        totv += a[i].v;
    /*   for (i=0; i<n; i++)
    	 { printf("\n Вес %d-го предмета =>",i+1);
    		scanf("%d",&a[i].w);
    		printf("\n Стоимость %d-го предмета =>",i+1);
    		scanf("%d",&a[i].v); totv = totv + a[i].v;
    	 }*/
    printf("\n totv=%d \n", totv);
    for (i = 0; i < n; i++)
        printf(" w[%d]=%d v[%d]=%d", i + 1, a[i].w, i + 1, a[i].v);
    w1 = 10;
    w2 = 10;
    w3 = 120;
    do
    {
        limw = w1;
        maxv = 0;
        for (i = 0; i < n; i++)
        {
            s[i] = -1;
            opts[i] = -1;
        }
        tryy(a, 0, 0, totv);
        printf("\n");
        w = 0;
        v = 0;
        for (i = 0; i < n; i++)
        {
            printf(" %d ", opts[i]);
            if (opts[i] > 0)
            {
                w = w + a[i].w;
                v = v + a[i].v;
            }
        }
        printf("   Вес рюкзака = %d    Стоимость = %d",
               w, v);
        printf(" K=%d", K);
        K = 0;
        w1 = w1 + w2;
    }
    while (w1 <= w3);
    printf("\n");
    getchar();
}

/* ******************************************************* */
