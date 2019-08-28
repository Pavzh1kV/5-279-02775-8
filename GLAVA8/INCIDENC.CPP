/* ПРОГРАММА ПРЕДСТАВЛЕНИЯ ОРГРАФА В ВИДЕ МАТРИЦЫ ИНЦИДЕНТНОСТИ */
/* Предусмотрен контроль  значений исходных данных    */
/* \incidenc.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
int main(void)
{
    setlocale(LC_ALL,"Russian");
    int i, j, vihod, vhod, number;
    int count = 0;		/* счетчик дуг */
    int P, Q, *B;		/* В - матрица инцидентности */
    printf
    ("\n ФОРМИРОВАНИЕ МАТРИЦЫ ИНЦИДЕНТНОСТИ ДЛЯ ОРГРАФА\n");
    /* Ввод числа вершин P и дуг Q */
    while (1)
    {
        printf("\n Введите число вершин P => ");
        fflush(NULL);
        if (!scanf("%d", &P) || P < 2)
        {
            printf("\nОШИБКА!");
            continue;
        }
        break;
    }
    while (1)
    {
        printf(" \n Введите число дуг Q => ");
        fflush(NULL);
        if (!scanf("%d", &Q))
        {
            printf("\n ОШИБКА!");
            continue;
        }
        if (Q > P * (P - 1))
        {
            printf("\n ОШИБКА !! слишком много дуг");
            continue;
        }
        break;
    }
    /* Получение памяти для матрицы инцидентности */
    B = (int *) calloc(P * Q, sizeof(int));
    /* Обнуление матрицы B[i][j] - можно было и не обнулять
       с учетом того, что функция calloc сама обнуляет
       выделяемую память */
    for (i = 0; i < P; i++)
        for (j = 0; j < Q; j++)
            B[i * Q + j] = 0;
    printf
    ("\nВвод данных и заполнение матрицы инцидентности\n");
    for (i = 0; i < P; i++)  	/* для каждой вершины */
    {
        while (1)
        {
            printf
            ("\nКоличество дуг, выходящих из вершины %d=>",
             i + 1);
            fflush(NULL);
            if (!scanf("%d", &vihod) || vihod > Q)
            {
                printf("\n ОШИБКА!");
                continue;
            }
            if ((count + vihod) > 2 * Q)
            {
                printf("\nОШИБКА! Слишком много дуг");
                continue;
            }
            break;
        }
        count = count + vihod;
        for (j = 0; j < vihod; j++)
        {
            while (2)
            {
                printf
                ("\nВведите номер дуги, выходящей из вершины %d=>",
                 i + 1);
                if (!scanf("%d", &number) || number > Q)
                {
                    printf("\nОШИБКА!");
                    continue;
                }
                break;
            }
            B[i * Q + number - 1] = 1;
        }
        while (1)
        {
            printf
            ("\nКоличество дуг, входящих в вершину %d=>",
             i + 1);
            fflush(NULL);
            if (!scanf("%d", &vhod) || vhod > Q)
            {
                printf("\n ОШИБКА!");
                continue;
            }
            if ((count + vhod) > 2 * Q)
            {
                printf("\nОШИБКА! Слишком много дуг");
                continue;
            }
            break;
        }
        count = count + vhod;
        for (j = 0; j < vhod; j++)
        {
            while (2)
            {
                printf
                ("\nВведите номер дуги, входящей в вершину %d=>",
                 i + 1);
                if (!scanf("%d", &number) || number > Q)
                {
                    printf("\nОШИБКА!");
                    continue;
                }
                break;
            }
            B[i * Q + number - 1] = -1;
        }
    }
    /* Вывод матрицы инцидентности на экран */
    printf("\n Матрица инцидентности ");
    for (i = 0; i < P; i++)
    {
        printf("\n");
        for (j = 0; j < Q; j++)
            printf("%d  ", B[i * Q + j]);
    }
    getchar();
    return 0;
}

/* ************************************************************* */
