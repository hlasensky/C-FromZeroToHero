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
        v->vec[i] = i * 3;
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

void clone(vector_t *v, int *arr)
{
    for (int i = 0; i < v->size; i++)
    {
        arr[i] = v->vec[i];
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

int *resize(vector_t *v, unsigned int new_size)
{
    int *new_pointer = malloc(new_size * sizeof(int));
    if (new_pointer != NULL)
    {
        clone(v, new_pointer);
        free(v->vec);
        v->vec = new_pointer;
        v->size = new_size;
        return 0;
    }
    fprintf(stderr, "No memory");
}

void insert(vector_t *v, int vel, int index, int value)
{
    resize(v, ++vel);
    for (int i = vel - 1; i > 0; i--)
    {
        if (i > index)
        {
            v->vec[i] = v->vec[i - 1];
        }
        if (i == index)
        {
            v->vec[i] = value;
        }
    }
}

void append(vector_t *v, vector_t *w)
{
    int oldSize = v->size;
    int newSize = v->size + w->size;
    resize(v, newSize);
    for (int i = (oldSize); i < newSize; i++)
    {
        v->vec[i] = w->vec[(i - oldSize)];
    }
    free(w->vec);
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    vector_t newVec;
    vector_t vec2;
    vector_t scalar;
    // printArr(arr, 5);
    // nTimesArray(arr, 3, 5);
    // printArr(arr, 5);
    vector_ctor(&newVec, 5);
    vector_ctor(&vec2, 5);
    free(vec2.vec);
    vec2.vec = arr;
    printVec(&newVec);
    printf("\n");
    printVec(&vec2);
    printf("\n");
    insert(&newVec, 5, 2, 99);
    printVec(&newVec);
    printf("\n");
    append(&newVec, &vec2);
    printVec(&newVec);

    // add(&newVec, 8);
    // printVec(&newVec);

    // clone(&newVec, &clonedVect);
    // add(&clonedVect, 2);

    // scalarAdd(&newVec, &clonedVect);

    descrut(&newVec);
    descrut(&vec2);
    descrut(&scalar);
    return 0;
}