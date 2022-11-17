#include <stdio.h>
#include <math.h>
#include <stdbool.h>

struct pair_t
{
    int x;
    int y;
};

int divide(int dividend, int divisor, double *quotient)
{
    if (divisor == 0)
    {
        return 0;
    }
    *quotient = (double)dividend / (double)divisor;
    return 1;
}

void swap(int *first, int *second)
{
    int tpm = *first;
    *first = *second;
    *second = tpm;
}

void plusPlus(int *first)
{
    *first = *first + 1;
}

void printPair(struct pair_t *par)
{
    printf("x: %d\ny: %d\n", par->x, par->y);
}

void isFunction(struct pair_t arrOfPairs2[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int find = 0;
        for (int y = 0; y < len; y++)
        {
            if (arrOfPairs2[i].x == arrOfPairs2[y].x)
            {
                find++;
                if (arrOfPairs2[i].y == arrOfPairs2[y].y && find > 1)
                {
                    find--;
                }
            }
            if (find > 1)
            {
                printf("Is not a function!");
                return;
            }
        }
    }
    printf("Is a function!");
}

int rel_minmax(struct pair_t rel[5], struct pair_t *min, struct pair_t *max)
{
    min->x = rel[0].x;
    min->y = rel[0].y;
    max->x = rel[0].x;
    max->y = rel[0].y;
    for (int i = 0; i < 5; i++)
    {
        if (min->y > rel[i].y)
        {
            min->x = rel[i].x;
            min->y = rel[i].y;
        }
        if (max->y < rel[i].y)
        {
            max->x = rel[i].x;
            max->y = rel[i].y;
        }
    }
}

void pair_invert(struct pair_t *point)
{
    int tmp = point->x;
    point->x = point->y;
    point->y = tmp;
}

int main()
{
    /*
    int first, second;
    scanf("%d %d", &first, &second);
    printf("1. %d 2. %d\n", first, second);
    swap(&first, &second);
    printf("1. %d 2. %d\n", first, second);
    plusPlus(&first);
    printf("1. %d\n", first);

    int dividend, divisor;
    double quotient;
    scanf("%d %d", &dividend, &divisor);
    if (!divide(dividend, divisor, &quotient))
    {
        printf("Division by zero!\n");
        return 1;
    }
    printf("%d / %d = %f\n", dividend, divisor, quotient);
    */
    int len = 5;
    struct pair_t arrOfPairs[len];
    struct pair_t min, max;
    for (int i = 0; i < len; i++)
    {
        arrOfPairs[i].x = i;
        arrOfPairs[i].y = i + 2;
    }
    struct pair_t arrOfPairs2[] = {{1, 1}, {2, 2}, {3, 3}, {3, 4}, {5, 5}};
    printPair(&arrOfPairs[1]);
    pair_invert(&arrOfPairs[1]);
    printPair(&arrOfPairs[1]);
    isFunction(arrOfPairs2, len);
    rel_minmax(arrOfPairs2, &min, &max);
    printf("max\n");
    printPair(&max);
    printf("min\n");
    printPair(&min);
    return 0;
}

/*int main(void)
{
    int a = 0;
    int b = 42;
    int *p;
    p = &b;
    p = &a;
    (*p)++;
    *p++;
    p = NULL;
    return *p;
}*/