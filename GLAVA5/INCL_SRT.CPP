/* ********************************************** */
/* ФАЙЛ ВКЛЮЧЕНИЯ С ФУНКЦИЯМИ СОРТИРОВКИ ЦЕЛОЧИС-
	ЛЕННОГО МАССИВА  \incl_srt.cpp */
/* ============================================== */
/* ФУНКЦИЯ СОРТИРОВКИ МЕТОДОМ ПУЗЫРЬКА  */
void BblSort(int A[], int nn)
{
    int i, j, k, p;
    for (i = 0; i < nn - 1; i++)
    {
        p = 0;
        for (j = nn - 1; j > i; j--)
            if (A[j] < A[j - 1])
            {
                k = A[j];
                A[j] = A[j - 1];
                A[j - 1] = k;
                p = 1;
            }
        /* Если перестановок не было, то сортировка выполнена */
        if (p == 0)
            break;
    }
}

/* =================================================== */
/* ФУНКЦИЯ  СОРТИРОВКИ МЕТОДОМ ШЕЛЛА */
void Shell(int A[], int nn)
{
    int i, j, k, x, ii;
    k = (nn + 1) / 2;
    while (k >= 1)
    {
        for (i = k; i < nn; i++)
        {
            if (A[i - k] > A[i])
            {
                x = A[i];
                j = i - k;
M:
                A[j + k] = A[j];
                if (j > k)
                {
                    if (A[j - k] > x)
                    {
                        j = j - k;
                        goto M;
                    }
                }
                A[j] = x;
            }
        }
        if (k > 2)
            k = (k + 1) / 2;
        else
            k = k / 2;
    }
}

/* ================================================= */
/* СОРТИРОВКА ПИРАМИДОЙ (ДЕРЕВОМ) */
void HeapSort(int A[], int nn)
{
    void Sift(int A[], int L, int R);
    int L, R, x, i;
    L = nn / 2;
    R = nn - 1;
    /*  Построение пирамиды из исходного массива */
    while (L > 0)
    {
        L = L - 1;
        Sift(A, L, R);
    }
    /* Сортировка: пирамида => отсортированный массив */
    while (R > 0)
    {
        x = A[0];
        A[0] = A[R];
        A[R] = x;
        R--;
        Sift(A, L, R);
    }
}

/* ================================================ */
void Sift(int A[], int L, int R)
{
    int i, j, x, k;
    i = L;
    j = 2 * L + 1;
    x = A[L];
    if ((j < R) && (A[j] < A[j + 1]))
        j++;
    while ((j <= R) && (x < A[j]))
    {
        k = A[i];
        A[i] = A[j];
        A[j] = k;
        i = j;
        j = 2 * j + 1;
        if ((j < R) && (A[j] < A[j + 1]))
            j++;
    }
}

/* =============================================== */
/* ФУНКЦИЯ ШЕЙКЕРНОЙ СОРТИРОВКИ  */
void ShkrSort(int A[], int nn)
{
    int i, j, k, x, L, R;
    L = 1;
    R = nn - 1;
    k = nn - 1;
    do
    {
        for (j = R; j >= L; j--)
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        L = k + 1;
        for (j = L; j <= R; j++)
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        R = k - 1;
    }
    while (L < R);
}

/* ===========================================  */
/* ФУНКЦИЯ СОРТИРОВКИ ПРЯМЫМ ВЫБОРОМ  */
void StrSel(int A[], int nn)
{
    int i, j, x, k;
    for (i = 0; i < nn - 1; i++)
    {
        x = A[i];
        k = i;
        for (j = i + 1; j < nn; j++)
            if (A[j] < x)
            {
                k = j;
                x = A[k];
            }
        A[k] = A[i];
        A[i] = x;
    }
}

/* ============================================== */
/* ФУНКЦИЯ СОРТИРОВКИ ПРЯМЫМ ВКЛЮЧЕНИЕМ  */
void Sis(int A[], int nn)
{
    int i, j, k;
    for (j = 1; j < nn; j++)
    {
        k = A[j];
        i = j - 1;
        while (k < A[i] && i >= 0)
        {
            A[i + 1] = A[i];
            i -= 1;
        }
        A[i + 1] = k;
    }
}

/* ============================================= */
/* ФУНКЦИЯ  БЫСТРОЙ СОРТИРОВКИ QuickSort */
void QuickSort(int A[], int L, int R)
{
    int i, j, k, x, m;
    i = L;
    j = R;
    x = A[(L + R) / 2];
    do
    {
        while (A[i] < x)
            i++;
        while (x < A[j])
            j--;
        if (i <= j)
        {
            k = A[i];
            A[i] = A[j];
            A[j] = k;
            i++;
            j--;
        }
    }
    while (i < j);
    if (L < j)
        QuickSort(A, L, j);
    if (i < R)
        QuickSort(A, i, R);
}

/* =========================================== */
/*  ФУНКЦИЯ ОБМЕННОЙ СОРТИРОВКИ по Топпу */
void ExchngSort(int A[], int nn)
{
    int i, j, k, p;
    /*	printf("\n Отладочная печать по шагам сортировки");*/
    for (i = 0; i < nn - 1; i++)
    {
        for (j = i + 1; j < nn; j++)
            if (A[i] > A[j])
            {
                k = A[j];
                A[j] = A[i];
                A[i] = k;
            }
        /*	  printf(" \ni = %d",i);
        	  for (j=0; j<nn;j++)
        		  printf("\t %d",A[j]);*/
    }
}

/* **************************************************** */
