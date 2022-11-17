#include <stdio.h>
#include <stdlib.h>

typedef struct vector
{
    int *vec;
    int size;
} vector_t;

void init(vector_t *v)
{
    for (int i = 0; i < v->size; i++)
    {
        v->vec[i] = 0;
    }
}

int vector_ctor(vector_t *v, unsigned int size)
{
    int *point = malloc(sizeof(int) * size);
    if (point == NULL)
    {
        v->size = 0;
        fprintf(stderr, "No memory left!");
        return 0;
    }
    v->vec = point;
    v->size = size;
    init(v);
    return 1;
}



void descrut(vector_t *v)
{
    free(v->vec);
    v->vec = NULL;
    v->size = 0;
}

void add(vector_t *v, int value)
{
    for (int i = 0; i < v->size; i++)
    {
        v->vec[i] += value;
    }
}

void clone(vector_t *v, vector_t *w)
{
    int point = vector_ctor(w, v->size);
    for (int i = 0; i < v->size; i++)
    {
        w->vec[i] = v->vec[i];
    }
}

void scalarAdd(vector_t *v, vector_t *w)
{
    int value = 0;
    for (int i = 0; i < v->size; i++)
    {
        value += (v->vec[i] * w->vec[i]);
    }
    printf("%d\n", value);
}

void printVec(vector_t *v)
{
    printf("[");
    for (int i = 0; i < v->size; i++)
    {
        if (i == v->size - 1)
        {
            printf("%d", v->vec[i]);
            break;
        }
        printf("%d,", v->vec[i]);
    }
    printf("]");
}

void printArr(int *arr, int vel)
{
    printf("[");
    for (int i = 0; i < vel; i++)
    {
        if (i == vel - 1)
        {
            printf("%d", arr[i]);
            break;
        }
        printf("%d,", arr[i]);
    }
    printf("]");
}

void nTimesArray(int *arr, int cNumber, int vel)
{
    for (int i = 0; i < vel; i++)
    {
        arr[i] *= cNumber;
    }
}

void insert(int *arr, int vel, int index, int value)
{
    for (int i = vel - 1; i > 0; i--)
    {
        if (i > index)
        {
            arr[i] = arr[i - 1];
        }
        if (i == index)
        {
            arr[i] = value;
        }
    }
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    vector_t newVec;
    vector_t clonedVect;
    vector_t scalar;
    // printArr(arr, 5);
    // nTimesArray(arr, 3, 5);
    // printArr(arr, 5);
    // insert(arr, 5, 2, 99);
    // printArr(arr, 5);
    vector_ctor(&newVec, 5);
    printVec(&newVec);

    add(&newVec, 8);
    printVec(&newVec);

    clone(&newVec, &clonedVect);
    add(&clonedVect, 2);
    printVec(&clonedVect);

    scalarAdd(&newVec, &clonedVect);


    descrut(&newVec);
    descrut(&clonedVect);
    descrut(&scalar);
    return 0;
}