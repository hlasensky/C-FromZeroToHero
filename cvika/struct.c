#include <stdio.h>

typedef struct output
{
    int result;
    double remainder;
    int errorCode;
} TOutput;

TOutput div(int firstValue, int secondValue)
{
    TOutput resDiv;
    double resultReminder;
    int result;
    if (secondValue == 0)
    {
        printf("Cannot divide by 0");
        resDiv.errorCode = 1;
        return resDiv;
    }
    result = firstValue / secondValue;
    resultReminder = firstValue % secondValue;
    resDiv.remainder = resultReminder;
    resDiv.errorCode = 0;
    resDiv.result = result;
    return resDiv;
}

TOutput add(int firstValue, int secondValue)
{
    TOutput resAdd;
    int result;
    result = firstValue + secondValue;
    resAdd.result = result;
    resAdd.errorCode = 0;
    return resAdd;
}

int pointersDiv(int firstValue, int secondValue, int *resultPointer, double *reminderPointer)
{
    int errorCode;
    if (secondValue == 0)
    {
        printf("Cannot divide by 0");
        errorCode = 1;
        return errorCode;
    }
    *resultPointer = firstValue / secondValue;
    *reminderPointer = firstValue % secondValue;
    errorCode = 0;
    return errorCode;
}

int main()
{

    int a;
    int b;
    printf("Enter first value: ");
    scanf("%d", &a);
    printf("Enter second value: ");
    scanf("%d", &b);

    TOutput resDiv;
    TOutput resAdd;
    int resPointers;

    //resDiv = div(a, b);
    resAdd = add(a, b);
    resPointers = pointersDiv(a, b, &resDiv.result, &resDiv.remainder);

    //printf("Values for division result: %d, remainder: %f, error code: %d\n", resDiv.result, resDiv.remainder, resDiv.errorCode);
    printf("Values for addition result: %d, error code: %d\n", resAdd.result, resAdd.errorCode);
    printf("Values for division result pointers: %d, remainder: %f, error code: %d\n", resDiv.result, resDiv.remainder, resPointers);
    
    return 0;
}