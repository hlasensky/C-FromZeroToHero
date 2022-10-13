#include <stdio.h>
#include <string.h>

void onlyOnes(int *numbersInArray)
{
    int find = 0;
    for (int numACounter = 0; numACounter < 5; numACounter++)
    {
        int findNum = 0;
        for (int numBCounter = 0; numBCounter < 5; numBCounter++)
        {
            if (numbersInArray[numACounter] == numbersInArray[numBCounter])
            {
                findNum++;
            }
        }
        if (findNum > 1)
        {
            find++;
        }
    }
    if (find)
    {
        printf("Array include duplicates\n");
    }
    else
    {
        printf("Array don't include duplicates\n");
    }
}

void absoluteNumbers(int *numbersInArray)
{
    for (int numberCounter = 0; numberCounter < 5; numberCounter++)
    {
        int x = numbersInArray[numberCounter];
        if (x < 0)
            printf("Absolute number: %d\n", -(x));
        else

            printf("Absolute number: %d\n", x);
    }
}

int compareTwoArrays(int *numbersInArrayA, int *numbersInArrayB)
{
    int find = 0;
    for (int numACounter = 0; numACounter < 5; numACounter++)
    {
        int findNum = 0;
        for (int numBCounter = 0; numBCounter < 5; numBCounter++)
        {
            if (numbersInArrayA[numACounter] == numbersInArrayB[numBCounter])
            {
                findNum++;
            }
        }
        if (findNum >= 1)
        {
            find++;
        }
    }
    return find;
}

int main()
{
    int a[5] = {3, -6, 9, -12, -128};
    int b[5] = {2, 38, 9, 9, 3};

    absoluteNumbers(a);
    onlyOnes(b);
    int findDups = compareTwoArrays(a, b);
    printf("Number of duplicates in arrays is: %d", findDups);
    return 0;
}