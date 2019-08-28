/* *************************************************** */
/* РАБОТА С В-ДЕРЕВЬЯМИ        b_tree.cpp                                        */

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#define n 2			/* n - порядок В-дерева */
#define nn 4			/* nn - макс. число элементов в узле */
#define Item struct II
#define Page struct PP
Item				/* структура элемента */
{
    int key;			/* ключ элемента */
    Page *p;			/* указатель на узел-потомок */
    int count;			/* данные */
};

Page				/* структура узла (страницы) */
{
    int m;			/* Число реальных элементов */
    Item e[nn + 1];
};

Page *root, *q;
int x, h;
FILE *out;
int d = 0;
void Del_Btree(Page **);
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

int AddEl(int x, Page * a, Item * v)
{
    int i, L, R, k, h1;
    Page *b;
    Item u;
    /* Поиск элемента с ключом х на странице *а */
    h1 = 0;
    if (a == NULL)  		/* дерево пустое или дошли до листа */
    {
        h1 = 1;
        v->key = x;
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
            if (x <= a->e[k].key)
                R = k - 1;
            if (x >= a->e[k].key)
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
                    printf(" b=%p", b);
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

/* ===================================================== */
/* НАЧАЛЬНАЯ ФУНКЦИЯ ДОБАВЛЕНИЯ ЭЛЕМЕНТА в В-дерево */
void AddEl1(int x, Page ** root)
{
    int h;
    Item u;
    Page *temp;
    temp = *root;
    h = AddEl(x, *root, &u);
    if (h)
    {
        *root = temp;
        q = *root;
        *root = (Page *) calloc(1, sizeof(Page));
        printf(" root=%p", *root);
        getchar();		/* новый корень */
        temp = *root;
        temp->m = 1;
        temp->e[0].p = q;
        temp->e[1] = u;
        *root = temp;
    }
}

/* ======================================================== */
/* ФУНКЦИЯ ПЕЧАТИ ДЕРЕВА - используется для демонстрации
	динамики изменения дерева при добавлении и удалении
	элементов. р - корень дерева */
void PrBtree(Page * p)
{
    int i;
    if (p == NULL && d == 0)
    {
        printf("\n Дерево пустое");
        return;
    }
    d++;
    if (p != NULL)
    {
        printf("   ");
        fprintf(out, "  ");
        for (i = 1; i <= p->m; i++)
        {
            printf(" %d ", p->e[i].key);
            fprintf(out, " %d ", p->e[i].key);
        }
        printf("\n");
        fprintf(out, "\n");
        for (i = 0; i <= p->m; i++)
            PrBtree(p->e[i].p);
    }
}

/* ========================================================= */
/* ФУНКЦИЯ, РЕАЛИЗУЮЩАЯ ЧАСТЬ АЛГОРИТМА УДАЛЕНИЯ
   ЭЛЕМЕНТА ИЗ ДЕРЕВА */
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
            printf("\n under=%p", b);
            h1 = c->m < n;
        }
    }
    else
    {
        /* b := страница слева от а */
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
        else  		/* слияние страниц а и b */
        {
            b->e[mb] = c->e[s];
            b->e[mb].p = a->e[0].p;
            for (i = 1; i <= n - 1; i++)
                b->e[i + mb] = a->e[i];
            b->m = nn;
            c->m = mc - 1;
            free(a);
            printf(" del a=%p", a);
            a = NULL;
            getchar();		/* отладка */
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
   ЭЛЕМЕНТА ИЗ ДЕРЕВА. Вызывается из начальной функции Delete1 */
int delet(int x, Page * a)
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
        printf("\n ключ %d не найден", x);
        h1 = 0;
    }
    else
    {
        L = 1;
        R = a->m;		/*двоичный поиск в массиве */
        do
        {
            k = (L + R) / 2;
            if (x <= a->e[k].key)
                R = k - 1;
            if (x >= a->e[k].key)
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
/* НАЧАЛЬНАЯ ФУНКЦИЯ УДАЛЕНИЯ ЭЛЕМЕНТА из В-дерева */
void Delete1(int x, Page ** root)
{
    int h;
    Page *temp, *t;
    temp = *root;
    h = delet(x, *root);
    t = *root;
    if (h)			/* уменьшен размер корневой страницы */
        if (t->m == 0)
        {
            *root = temp;
            q = *root;
            temp = q->e[0].p;
            free(q);
            *root = temp;	/* высота дерева уменьшилась */
            printf(" del q=%p", q);
            getchar();		/*удаленный узел-корень */
            q = NULL;
        }
}

/* =================================================== */
/* НИСХОДЯЩИЙ ОБХОД ДЕРЕВА - рекурсивная функция
	Т - корень дерева, level - уровень поддерева  */
void preorder(Page * T, int level)
{
    int i;			/* i - счетчик цикла */
    if (T == NULL && d == 0)
    {
        printf("\n Дерево пустое");
        return;
    }
    d++;
    if (T == NULL)
        return;
    printf("\n Уровень %d >", level);
    fprintf(out, "\n Level %d >", level);
    printf(" p[0]=%p", T->e[0].p);
    for (i = 1; i < T->m + 1; i++)
    {
        /* цикл печати содержимого *//* узла 'T' B-дерева */
        printf(" ключ=%d p[%d]=%p ", T->e[i].key, i, T->e[i].p);
        fprintf(out, " Key=%d ", T->e[i].key);
        printf(" сч=%d", T->e[i].count);
        getchar();
    }
    for (i = 0; i < T->m + 1; i++)	/* цикл обхода потомков */
        preorder(T->e[i].p, level + 1);
}

/* =========================================================== */
/*       ВОСХОДЯЩИЙ ОБХОД ДЕРЕВА     */
void postorder(Page * T, int level)
{
    int i;			/* счетчик цикла */
    if (T == NULL && d == 0)
    {
        printf("\n Дерево пустое");
        return;
    }
    d++;
    if (T == NULL)
        return;
    for (i = 0; i < T->m + 1; i++)	/* цикл обхода потомков */
        postorder(T->e[i].p, level + 1);
    printf("\n Уровень %d >", level);
    for (i = 1; i < (T->m + 1); i++)	/* цикл печати содержимого узла 'T' */
        printf(" %d ", T->e[i].key);
}

/* ============================================================= */
/*    СМЕШАННЫЙ ОБХОД ДЕРЕВА     */
void inorder(Page * T)
{
    int i;			/* счетчик цикла */
    if (T == NULL && d == 0)
    {
        printf("\n Дерево пустое");
        return;
    }
    d++;
    if (T == NULL)
        return;
    inorder(T->e[0].p);
    for (i = 1; i < T->m + 1; i++)  	/* цикл обхода потомков */
    {
        printf(" %d ", T->e[i].key);
        inorder(T->e[i].p);
    }
}

/* ===================================================== */
/* ФУНКЦИЯ УДАЛЕНИЯ ДЕРЕВА */
/* void Del_Btree(Page **t)
 { int i; Page *T; T=*t;
	if (T==NULL)
	  return;
	for (i=0; i<T->m+1; i++)
		 Del_Btree(&T->e[i].p);
	printf(" delT=%p"); getchar();
	free(T);T=NULL; *t=T;
 }*/
/* ==================================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i;
    out = fopen("c:\\bc\\rezbtree.txt", "w");
    root = NULL;
    printf("\n Создание В-дерева");
    fprintf(out, "\n Создание В-дерева");
    for (i = 1; i < 22; i++)
    {
        /*printf("\n Введите %d-й ключ =>",i);
        			   scanf("%d",&x);  printf("\n Элемент %d:\n",x); */
        AddEl1(i, &root);
        printf("\n");
        getchar();
        d = 0;
        PrBtree(root);
    }
    printf("\n дерево создано. ");
    getchar();
    fprintf(out, "\n дерево создано.");
    printf("\n Нисходящий обход");
    fprintf(out, "\n Preorder:");
    d = 0;
    preorder(root, 0);
    getchar();
    printf("\n Восходящий обход");
    fprintf(out, "\n Postorder:");
    d = 0;
    postorder(root, 0);
    getchar();
    printf("\n Смешанный обход");
    fprintf(out, "\n Inorder");
    d = 0;
    inorder(root);
    getchar();
    printf("\n Удаление элементов");
    fprintf(out, "\n Delete key\n");
    for (i = 1; i < 4; i++)
    {
        printf("\n Введите %d-й ключ =>", i);
        scanf("%d", &x);
        fprintf(out, "\n Key= %d:\n ", x);
        Delete1(x, &root);
        d = 0;
        PrBtree(root);
        d = 0;
        preorder(root, 0);
    }
    fclose(out);
    printf("\n Удаляем дерево");
    Del_Btree(&root);
    d = 0;
    preorder(root, 0);
    d = 0;
    postorder(root, 0);
    d = 0;
    inorder(root);
    d = 0;
    PrBtree(root);
    getchar();
}

/* ================================================= */
/*ФУНКЦИЯ ОСВОБОЖДЕНИЯ ПАМЯТИ,ЗАНЯТОЙ УЗЛАМИ ДЕРЕВА */
void Del_Btree(Page ** t)
{
    int i;
    Page *T;
    static int s = 1;
    T = *t;
    printf(" s=%d T=%p", s++, T);
    getchar();
    if (T == NULL)
        return;
    if (T->e[0].p == 0)
    {
        free(T);
        printf(" T1=%p", T);
        getchar();
        T = NULL;
        *t = T;
        return;
    }
    else
        for (i = 0; i < T->m + 1; i++)
            Del_Btree(&(T->e[i].p));
    free(T);
    printf(" T2=%p", T);
    T = NULL;
    *t = T;
    getchar();
}

/* ******************************************************* */
