
#include <stdio.h>
#include <string.h>

void printArray(int *array)
{
    for (int i = 0; i < strlen(array); ++i)
    {
        printf("%s\n", array[i]);
    }
}