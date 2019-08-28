/* *************************************************** */
/* РАБОТА С В-ДЕРЕВЬЯМИ. Объединение двух деревьев     */
/* Исходные деревья уничтожаются. \unb_tree.cpp        */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
#define n 2			/* n - порядок В-дерева */
#define nn 4			/* nn - макс. число элементов в узле */
#define Item struct II
#define Page struct PP
char *menu[21][30];
int pp;
Item
{
    char State[20], Capit[20];
    float SQR, Popul;
    Page *p;
    int count;			/* счетчик повторяющихся ключей */
};

Page
{
    int m;			/* Число элементов */
    Item e[nn + 1];
};

Page *root, *q, *root2, *root3;
int h;
Item x, u;
void ins(Item x, Page * a);
int AddEl(Item x, Page * a, Item * v);
int PrBtree(Page * p);
void postorder(Page * T, int level);
void Main_Menu(void);
int underflow(Page * c, Page * a, int s);
void vvod();
void AddEl1(Item x, Page ** T);
int del(Page * p, Page * a, int k);
void preorder(Page * T, int level);
int delet(Item x, Page * a);
void inorder(Page * T);
void UniBtree(Page * T);
void Del_BTree(Page ** T);
int ss = 0;			/* для определения пустоты дерева */
/* ===================================================== */
/* НАЧАЛЬНАЯ ФУНКЦИЯ ДОБАВЛЕНИЯ ЭЛЕМЕНТА в В-дерево */
void AddEl1(Item x, Page ** T)
{
    int h;
    Item u;
    Page *temp;
    temp = *T;
    h = AddEl(x, *T, &u);
    if (h)
    {
        *T = temp;
        q = *T;
        *T = (Page *) calloc(1, sizeof(Page));
        temp = *T;
        temp->m = 1;
        temp->e[0].p = q;
        temp->e[1] = u;
        *T = temp;
    }
}

/* ======================================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i, col1, col2, col3;
    pp = 1;
    root = NULL;
    root2 = NULL;
    root3 = NULL;
    system("clear");
    *menu[1] =
        "1. Создание 1-ого Б-дерева государств";
    *menu[2] =
        "2. Создание 2-ого Б-дерева государств ";
    *menu[3] = "3. Нисходящий обход 1-ого дерева";
    *menu[4] = "4. Восходящий обход 1-ого дерева";
    *menu[5] = "5. Смешанный обход 1-ого дерева";
    *menu[6] = "6. Нисходящий обход 2-ого дерева";
    *menu[7] = "7. Восходящий обход 2-ого дерева";
    *menu[8] = "8. Смешанный обход 2-ого дерева";
    *menu[9] =
        "9. Включение элемента в 1-ое дерево ";
    *menu[10] =
        "10. Удаление элемента из 1-ого дерева ";
    *menu[11] =
        "11. Включение элемента во 2-ое дерево";
    *menu[12] =
        "12. Удаление элемента из 2-ого дерева";
    *menu[13] = "13.Вывод 1-ого дерева ";
    *menu[14] = "14.Вывод 2-ого дерева ";
    *menu[15] = "15.Вывод 3-ого дерева ";
    *menu[16] =
        "16.Объединение данных о государстве из первого и второго деревьев в третье";
    *menu[17] =
        "17. Включение элемента в 3-ое дерево ";
    *menu[18] =
        "18. Удаление элемента из 3-ого дерева ";
    *menu[19] = "19.Конец работы";
    *menu[20] = "         Введите номер строки";
    system("clear");
    printf("     РАБОТА С Б-ДЕРЕВЬЯМИ \n");
    while (pp)
    {
        Main_Menu();
        system("clear");
    }
    printf("    Конец pаботы с деревом\n");
    getchar();
    return 0;
}

/* ===================================================== */
/* Рекурсивная функция включения  элемента с ключом х
	в В-дерево с корнем *а. Осуществляется поиск элемента
   с таким ключом.
   Если элемент с ключом х уже есть, то счетчик элемента
   count увеличивается на 1, иначе в дерево включается
   элемент с ключом х и счетчиком 1. Если элемент должен
   передаваться на низший уровень, то он присваивается v,
   и дерево станет выше, признак роста дерева присаивается
   h1 и возвращается через имя функции вызывающей функции. */

int AddEl(Item x, Page * a, Item * v)
{
    int i, L, R, k, h1;
    Page *b;
    Item u;
    /* Поиск элемента с ключом х на странице *а */
    h1 = 0;
    if (a == NULL)  		/* дерево пустое или дошли до листа */
    {
        h1 = 1;
        strcpy(v->State, x.State);
        strcpy(v->Capit, x.Capit);
        v->SQR = x.SQR;
        v->Popul = x.Popul;
        v->count = 1;
        v->p = NULL;
    }
    else  			/* двоичный поиск элемента на странице */
    {

        L = 1;
        R = a->m;
        do
        {
            k = (L + R) / 2;
            if (strcmp(x.State, a->e[k].State) <= 0)
                R = k - 1;
            if (strcmp(x.State, a->e[k].State) >= 0)
                L = k + 1;
        }
        while (R >= L);
        if ((L - R) > 1)  	/* дубль-ключ */
        {
            a->e[k].count++;
            h1 = 0;
            printf("\n дубль-ключ");
        }
        else  		/* на этой странице элемента нет */
        {

            if (R == 0)
                q = a->e[0].p;
            else
                q = a->e[R].p;
            h1 = AddEl(x, q, &u);
            if (h1)		/* дошли до листа, ключ - не дубль */
                if (a->m < nn)  	/* есть место на странице */
                {
                    h1 = 0;
                    a->m = a->m + 1;
                    for (i = a->m; i >= R + 2; i--)
                        a->e[i] = a->e[i - 1];
                    a->e[R + 1] = u;
                }
                else  	/* страница полна, расщепляем ее */
                {

                    b = (Page *) calloc(1, sizeof(Page));
                    if (R <= n)
                    {
                        if (R == n)
                            *v = u;
                        else
                        {
                            *v = a->e[n];
                            for (i = n; i >= R + 2; i--)
                                a->e[i] = a->e[i - 1];
                            a->e[R + 1] = u;
                        }
                        for (i = 1; i <= n; i++)
                            b->e[i] = a->e[i + n];
                    }
                    else  	/*включение в правую страницу */
                    {

                        R = R - n;
                        *v = a->e[n + 1];
                        for (i = 1; i <= R - 1; i++)
                            b->e[i] = a->e[i + n + 1];
                        b->e[R] = u;
                        for (i = R + 1; i <= n; i++)
                            b->e[i] = a->e[i + n];
                    }
                    a->m = n;
                    b->m = n;
                    b->e[0].p = v->p;
                    v->p = b;
                    h1 = 1;
                }
        }
    }
    return h1;
}

/* ============================================= */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
void Main_Menu(void)
{
    int ns, col1, col2, col3, i;
    fflush(NULL);			/* чистка буферов */
    while (1)
    {
        for (i = 1; i < 21; i++)
            printf("\n %s", *menu[i]);
        printf("\n");
        if ((scanf("%d", &ns) < 1) || ns < 1 || ns > 20)
        {
            fflush(NULL);
            system("clear");
            printf
            ("\nОшибка в номере!!Будьте внимательны.");
            continue;
        }
        break;
    }
    switch (ns)
    {
    case 1:
    {
        root = 0;
        col1 = 0;
        printf
        ("Введите количество государств");
        scanf("%d", &col1);
        for (i = 0; i < col1; i++)
        {
            vvod();
            AddEl1(x, &root);
            ss = 0;
            PrBtree(root);
        }
        break;
    }
    case 2:
    {
        root2 = 0;
        printf
        ("Введите количество государств");
        scanf("%d", &col2);
        for (i = 0; i < col2; i++)
        {
            vvod();
            AddEl1(x, &root2);
            ss = 0;
            PrBtree(root2);
        }
        break;
    }
    case 3:
    {
        preorder(root, 0);
        getchar();
        break;
    }
    case 4:
    {
        postorder(root, 0);
        getchar();
        break;
    }
    case 5:
    {
        inorder(root);
        getchar();
        break;
    }
    case 6:
    {
        preorder(root2, 0);
        getchar();
        break;
    }
    case 7:
    {
        postorder(root2, 0);
        getchar();
        break;
    }
    case 8:
    {
        inorder(root2);
        getchar();
        break;
    }
    case 13:
    {
        ss = 0;
        PrBtree(root);
        getchar();
        break;
    }
    case 14:
    {
        ss = 0;
        PrBtree(root2);
        getchar();
        break;
    }
    case 9:
    {
        vvod();
        AddEl1(x, &root);
        break;
    }
    case 11:
    {
        vvod();
        AddEl1(x, &root2);
        break;
    }
    case 10:
    {
        printf("\n Введите государство =>");
        scanf("%s", &x.State);
        h = delet(x, root);
        if (h)		/* уменьшен размер корневой страницы */
            if (root->m == 0)
            {
                q = root;
                root = q->e[0].p;
                free(q);
            }
        break;
    }
    case 12:
    {
        printf("\n Введите государство =>");
        scanf("%s", &x.State);
        h = delet(x, root2);
        if (h)		/* уменьшен размер корневой страницы */
            if (root->m == 0)
            {
                q = root2;
                root2 = q->e[0].p;
                free(q);
            }
        break;
    }
    case 16:
    {
        UniBtree(root);
        ss = 0;
        PrBtree(root3);
        getchar();
        UniBtree(root2);
        ss = 0;
        PrBtree(root3);
        getchar();
        Del_BTree(&root);
        Del_BTree(&root2);
        break;
    }
    case 15:
    {
        ss = 0;
        PrBtree(root3);
        getchar();
        break;
    }
    case 17:
    {
        vvod();
        AddEl1(x, &root3);
        break;
    }
    case 18:
    {
        printf("\n Введите государство =>");
        scanf("%s", &x.State);
        h = delet(x, root3);
        if (h)		/* уменьшен размер корневой страницы */
            if (root3->m == 0)
            {
                q = root3;
                root3 = q->e[0].p;
                free(q);
            }
        break;
    }
    case 19:
        pp = 0;
    }
}

/* ===================================================== */
/* ПЕЧАТЬ ДЕРЕВА - используется для демонстрации динамики
	изменения дерева при добавлении и удалении элементов.
	р - корень дерева */
int PrBtree(Page * p)
{
    int i;
    if (!ss && !p)
    {
        printf("\n Дерево пустое");
        return -1;
    }
    if (p != NULL)
    {
        printf("\n");
        ss++;
        for (i = 1; i <= p->m; i++)
            printf("\n гос.%s стол.%s пл.%f нас.%f ",
                   p->e[i].State, p->e[i].Capit, p->e[i].SQR,
                   p->e[i].Popul);
        printf("\n");
        for (i = 0; i <= p->m; i++)
            PrBtree(p->e[i].p);
    }
    return 0;
}

/* ========================================================= */
/* ФУНКЦИЯ, РЕАЛИЗУЮЩАЯ ЧАСТЬ АЛГОРИТМА УДАЛЕНИЯ
   ЭЛЕМЕНТА ИЗ ДЕРЕВА. */
int underflow(Page * c, Page * a, int s)
/* а - страница с нехваткой, с - страница-предок */
{
    Page *b;
    int i, k, mb, mc, h1;
    mc = c->m;
    h1 = 1;			/* a->m==n-1 */
    if (s < mc)  		/* b:=страница справа от а */
    {
        s = s + 1;
        b = c->e[s].p;
        mb = b->m;
        k = (mb - n + 1) / 2;
        /* k - число элементов на соседней странице b */
        a->e[n] = c->e[s];
        a->e[n].p = b->e[0].p;
        if (k > 0)  		/* пересылка k элементов с b на а */
        {
            for (i = 1; i <= k - 1; i++)
                a->e[i + n] = b->e[i];
            c->e[s] = b->e[k];
            c->e[s].p = b;
            b->e[0].p = b->e[k].p;
            mb = mb - k;
            for (i = 1; i <= mb; i++)
                b->e[i] = b->e[i + k];
            b->m = mb;
            a->m = n - 1 + k;
            h1 = 0;
        }
        else  		/*слияние страниц а и b */
        {
            for (i = 1; i <= n; i++)
                a->e[i + n] = b->e[i];
            for (i = s; i <= mc - 1; i++)
                c->e[i] = c->e[i + 1];
            a->m = nn;
            c->m = mc - 1;
            free(b);
            h1 = c->m < n;
        }
    }
    else  			/* b := страница слева от а */
    {
        if (s == 1)
            b = c->e[0].p;
        else
            b = c->e[s - 1].p;
        mb = b->m + 1;
        k = (mb - n) / 2;
        if (k > 0)  		/* пересылка k элементов со страницы b на a */
        {
            for (i = n - 1; i >= 1; i--)
                a->e[i + k] = a->e[i];
            a->e[k] = c->e[s];
            a->e[k].p = a->e[0].p;
            mb = mb - k;
            for (i = k - 1; i >= 1; i--)
                a->e[i] = b->e[i + mb];
            a->e[0].p = b->e[mb].p;
            c->e[s] = b->e[mb];
            c->e[s].p = a;
            b->m = mb - 1;
            a->m = n - 1 + k;
            h1 = 0;
        }
        else  		/* слияние странц а и b */
        {
            b->e[mb] = c->e[s];
            b->e[mb].p = a->e[0].p;
            for (i = 1; i <= n - 1; i++)
                b->e[i + mb] = a->e[i];
            b->m = nn;
            c->m = mc - 1;
            free(a);
            h1 = (c->m < n);
        }
    }
    return h1;
}

/* ========================================================= */
/* РЕКУРСИВНАЯ ФУНКЦИЯ, РЕАЛИЗУЮЩАЯ ЧАСТЬ АЛГОРИТМА УДАЛЕНИЯ
   ЭЛЕМЕНТА ИЗ ДЕРЕВА */
int del(Page * p, Page * a, int k)
{
    Page *q;
    int h1;
    q = p->e[p->m].p;
    if (q != NULL)
    {
        h1 = del(q, a, k);
        if (h1)
            h1 = underflow(p, q, p->m);
    }
    else
    {
        p->e[p->m].p = a->e[k].p;
        a->e[k] = p->e[p->m];
        p->m = p->m - 1;
        h1 = (p->m < n);
    }
    return h1;
}

/* ======================================================= */
/* РЕКУРСИВНАЯ ФУНКЦИЯ, РЕАЛИЗУЮЩАЯ ЧАСТЬ АЛГОРИТМА УДАЛЕНИЯ
   ЭЛЕМЕНТА ИЗ ДЕРЕВА. Вызывается из главной процедуры */
int delet(Item x, Page * a)
/* поиск и удаление ключа х в В-дереве а. Если
   при удалении на странице останется мало элементов,
   то балансировка с соседней страницей либо слияние.
   h1=true при нехватке элементов на странице */
{
    int i, k, L, R;
    Page *q;
    int h1;
    if (a == NULL)
    {
        printf("\n Государство %s не найдено",
               x.State);
        getchar();
        h1 = 0;
    }
    else
    {
        L = 1;
        R = a->m;		/*двоичный поиск в массиве */
        do
        {
            k = (L + R) / 2;
            if (strcmp(x.State, a->e[k].State) <= 0)
                R = k - 1;
            if (strcmp(x.State, a->e[k].State) >= 0)
                L = k + 1;
        }
        while (R >= L);
        if (R == 0)
            q = a->e[0].p;
        else
            q = a->e[R].p;
        if ((L - R) > 1)  	/*найден, теперь удаление e[k] */
        {
            if (q == NULL)  	/*a -терминальная страница */
            {
                a->m--;
                h1 = (a->m < n);
                for (i = k; i <= a->m; i++)
                    a->e[i] = a->e[i + 1];
            }
            else
            {
                h1 = del(q, a, k);
                if (h1)
                    h1 = underflow(a, q, R);
            }
        }
        else
        {
            h1 = delet(x, q);
            if (h1)
                h1 = underflow(a, q, R);
        }
    }
    return h1;
}

/* ========================================================= */
/* НИСХОДЯЩИЙ ОБХОД ДЕРЕВА - рекурсивная функция
	Т - корень дерева, level - уровень поддерева  */
void preorder(Page * T, int level)
{
    int i;			/* счетчик цикла */
    if (T == NULL)
        return;
    printf("\n Уровень %d >", level);
    for (i = 1; i < T->m + 1; i++)
    {
        /* цикл печати содержимого *//* узла 'T' B-дерева */
        printf("\n гос.%s стол.%s пл.%f нас.%f\n ",
               T->e[i].State, T->e[i].Capit, T->e[i].SQR, T->e[i].Popul);
        printf("сч=%d\n", T->e[i].count);
    }
    for (i = 0; i < T->m + 1; i++)	/* цикл обхода потомков */
        preorder(T->e[i].p, level + 1);
}

/* =========================================================== */
/*       ВОСХОДЯЩИЙ ОБХОД ДЕРЕВА     */
void postorder(Page * T, int level)
{
    int i;			/* счетчик цикла */
    if (T == NULL)
        return;
    for (i = 0; i < T->m + 1; i++)	/* цикл обхода потомков */
        postorder(T->e[i].p, level + 1);
    printf("\n Уровень %d >", level);
    for (i = 1; i < (T->m + 1); i++)	/* цикл печати содержимого узла 'T' */
        printf(" гос.%s стол.%s пл.%f нас.%f ", T->e[i].State,
               T->e[i].Capit, T->e[i].SQR, T->e[i].Popul);
}

/* =================================================== */
/*    СМЕШАННЫЙ ОБХОД ДЕРЕВА     */
void inorder(Page * T)
{
    int i;			/* счетчик цикла */
    if (T == NULL)
        return;
    inorder(T->e[0].p);
    for (i = 1; i < T->m + 1; i++)  	/* цикл обхода потомков      */
    {
        printf(" гос.%s стол.%s пл.%f нас.%f ", T->e[i].State,
               T->e[i].Capit, T->e[i].SQR, T->e[i].Popul);
        inorder(T->e[i].p);
    }
}

/* ===================================================== */
void vvod(void)
{
    printf("\n Введите государство =>");
    scanf("%s", &x.State);
    printf("\n Введите столицу =>");
    scanf("%s", &x.Capit);
    printf("\n Введите площадь =>");
    scanf("%f", &x.SQR);
    printf("\n Введите население =>");
    scanf("%f", &x.Popul);
}

/* ==================================================== */
/* ЛОГИЧЕКСКОЕ ОБЪЕДИНЕНИЕ ДВУХ В-ДЕРЕВЬВ */
void UniBtree(Page * p)
{
    int i;
    if (p != NULL)
    {
        for (i = 1; i <= p->m; i++)
            AddEl1(p->e[i], &root3);
        for (i = 0; i <= p->m; i++)
            UniBtree(p->e[i].p);
    }
}

/* ========================================================= */
/*ФУНКЦИЯ ОСВОБОЖДЕНИЯ ПАМЯТИ,ЗАНЯТОЙ УЗЛАМИ ДЕРЕВА*/
void Del_BTree(Page ** t)
{
    int i;
    Page *T;
    T = *t;
    if (T == NULL)
        return;
    if (T->e[0].p == 0)
    {
        free(T);
        T = NULL;
        *t = T;
        return;
    }
    else
        for (i = 0; i < T->m + 1; i++)
            Del_BTree(&(T->e[i].p));
    free(T);
    T = NULL;
    *t = T;
}

/* *************************************************** */
