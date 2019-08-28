/* ******************************************** */
/* ФАЙЛ ВКЛЮЧЕНИЯ ДЛЯ КОДИРОВАНИЯ И ДЕКОДИРОВАНИЯ
	ТЕКСТА ПО ХАФФМАНУ */
/* c:\bc\xbs\algoritm\incl_hfm.cpp              */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
typedef struct Rec
{
    char ch;
    unsigned int code;
    int ln;
};
/* Кодовая таблица */
Rec s[36] =
{
    'а', 0x0, 1,
    'о', 0x8, 4,
    'г', 0xc, 4,
    'в', 0x12, 5,
    'е', 0x14, 5,
    'к', 0x15, 5,
    'д', 0x16, 5,
    'н', 0x1c, 5,
    ' ', 0x1d, 5,
    'л', 0x1e, 5,
    'с', 0x26, 6,
    'и', 0x2e, 6,
    'м', 0x3e, 6,
    'т', 0x36, 6,
    'б', 0x34, 6,
    'я', 0x35, 6,
    'ж', 0x5e, 7,
    'п', 0x7e, 7,
    'р', 0x6e, 7,
    'з', 0x9e, 8,
    'х', 0x9c, 8,
    'ф', 0x9d, 8,
    'ю', 0xbe, 8,
    'ч', 0xfe, 8,
    'ш', 0xff, 8,
    'щ', 0xde, 8,
    'э', 0x13e, 9,
    'ц', 0x1be, 9,
    'й', 0x1bf, 9,
    'ь', 0x27e, 10,
    'ъ', 0x27f, 10,
    '.', 0x2fc, 10,
    ',', 0x2fd, 10,
    ';', 0x5fc, 11,
    'у', 0x5fd, 11,
    'ы', 0x5fe, 11
};


int l,				/* длина 8 unsigned int */
    lc,				/* длина кода */
    ls,				/* размер сдвига */
    lb;				/* длина занятой части в формируемом слове */
unsigned int r,			/* очередной обрабатываемый символ */
         r1, r3, r4,			/* вспомогательные слова */
         p;				/* формируемое слово */
/* ================================================= */
/* КОДИРОВАНИЕ ПО КОДОВОЙ ТАБЛИЦЕ ХАФФМАНА           */
int Code_Hfm(char *str, unsigned int *cstr)
{
    int i, j, k, nn;
    l = sizeof(unsigned int) * 8;
    /*  printf("\n Кодовая таблица:");
    	 for (i=0; i<36; i++)
    	 printf("\n %c\t %x\t %d",s[i].ch,s[i].code,s[i].ln);
    	 getchar();*/
    nn = strlen(str);
    cstr[0] = nn;
    p = 0;
    lb = 0;
    j = 1;
    /*	printf("\n Кодируем: %s\n",str);*/
    for (k = 0; k < nn; k++)
        for (i = 0; i < 36; i++)
            if (str[k] != s[i].ch)
                continue;
            else
            {
                r = s[i].code;
                lc = s[i].ln;
                if ((l - lb) == lc)
                {
                    p = p ^ r;
                    /* Вывод закодированного слова в файл */
                    cstr[j] = p;
                    j++;
                    lb = 0;
                    p = 0;
                    break;
                }
                if ((l - lb) > lc)
                {
                    ls = l - lb - lc;
                    r = r << ls;
                    p = p ^ r;
                    lb = lb + lc;
                    break;
                }
                r1 = r;
                ls = lc - (l - lb);
                r1 = r1 >> ls;
                p = p ^ r1;
                /* Вывод кодированного слова в файл */
                cstr[j] = p;
                j++;
                p = 0;
                r = r << (l - ls);
                p = p ^ r;
                lb = ls;
                break;
            }
    /* Вывод последнего неполного слова в файл */
    cstr[j++] = p;
    cstr[j] = '\0';
    /*	 printf("\n Результат кодирования:\n");
    	 puts(str);
    	 for(i=0; i<=nn; i++)
    		printf (" %x ",cstr[i]);
    	 getchar();*/
    return j * 2;		/* длина закодированной строки */
}

/* ================================================ */
/* ДЕКОДИРОВАНИЕ ПО ХАФФМАНУ */
int Dcde_Hfm(unsigned int *cstr, char *dstr)
{
    int i, j, k, t, nn;
    r = cstr[1];
    r1 = cstr[2];
    j = 3;
    r3 = r;
    k = 0;
    t = 0;
    lc = 1;
    lb = 16;
    nn = cstr[0];
    while (k < nn && lc < 12)
    {
        t = 0;
        r = r >> (l - lc);
        for (i = 0; i < 36; i++)	/* выделение очередного символа */
            if (r == s[i].code)
            {
                dstr[k++] = s[i].ch;
                t = 1;
                r = r3;
                r = r << lc;	/* удалили обработанные биты */
                /* заполним освободившиеся биты старшими битами из r1 */
                if (lc == lb)  	/*переносятся все биты из r1 */
                {
                    r1 = r1 >> (l - lb);
                    r = r ^ r1;
                    r1 = cstr[j++];
                    lb = 16;
                }
                else if (lb > lc)  	/* в r1 больше битов, чем требуется */
                {
                    r4 = r1;
                    r1 = r1 >> (l - lc);
                    r = r ^ r1;
                    r1 = r4;
                    r1 = r1 << lc;
                    lb = lb - lc;
                }
                else  	/*lc>lb, т.е. в r1 недостаточно битов */
                {

                    r1 = r1 >> (l - lc);
                    r = r ^ r1;
                    r1 = cstr[j++];
                    r4 = r1;
                    r1 = r1 >> (l - (lc - lb));
                    r = r ^ r1;
                    r1 = r4;
                    lb = lc - lb;
                    /* Из r1 удаляем старшие биты, перенесенные в r */
                    r1 = r1 << lb;
                    lb = 16 - lb;
                }
                r3 = r;
                lc = 1;
                break;
            }
        if (t)
        {
            r = r3;
            lc = 1;
        }
        else
        {
            r = r3;
            if (lc == 1)
                lc = 4;
            else
                lc = lc + 1;
        }
    }
    dstr[k] = '\0';
    /*	 printf("\n Результат декодирования:\n");
    	 puts(dstr); getchar();*/
    return 0;
}

/* *************************************************************** */
