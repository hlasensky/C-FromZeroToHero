#include <stdio.h>
#include <string.h>

struct namePlusPhone
{
    char name[101];
    char phone[101];
    int index;
};

int clearBuffer(char array[101])
{
    for (size_t i = 0; i <= 101; ++i)
        array[i] = 0;
}

char readFile(struct namePlusPhone arrayOfNamePlusPhone[42])
{
    char ch;
    char bufferArray[101];

    int index = 0;
    int i = 0;

    while (1)
    {
        ch = getchar();

        if (ch == EOF)
        {
            break;
        }

        if (ch == '\n')
        {
            if (index % 2 == 0)
            {
                strcpy(arrayOfNamePlusPhone[index / 2].name, bufferArray);
                i = 0;
                clearBuffer(bufferArray);
                arrayOfNamePlusPhone[index / 2].index = (index / 2);
            }
            else
            {
                strcpy(arrayOfNamePlusPhone[(index - 1) / 2].phone, bufferArray);
                i = 0;
                clearBuffer(bufferArray);
            }
            index++;
        }
        else
        {
            bufferArray[i] = ch;
            i++;
        }
    }
    return index / 2;
}

int findByNumber(char *sequenceOfNumbers, char *phoneNumber)
{
    int find;
    int counterSeqOFNum;
    find = 0;
    counterSeqOFNum = 0;
    for (int counterPhoneNumber = 0; counterPhoneNumber < strlen(phoneNumber); counterPhoneNumber++)
    {
        if (counterSeqOFNum == strlen(sequenceOfNumbers))
        {
            return find;
        }
        //printf("findNum seq: %c, phoneN: %c\n", sequenceOfNumbers[counterSeqOFNum], phoneNumber[counterPhoneNumber]);
        if (sequenceOfNumbers[counterSeqOFNum] == phoneNumber[counterPhoneNumber])
        {
            find++;
            counterSeqOFNum++;
        }
        else
        {
            find = 0;
            counterSeqOFNum = 0;
        }
    }

    return -1;
}

int findByString()
{
    return 0;
}

char *find(char *sequenceOfNumbers, struct namePlusPhone namePhoneArray[42], int numberOfContacts, char arrayOfIndexes[42])
{

    int counter = 0;
    int numberOfFindsInNum;
    int numberOfFindsInStr;
    for (int i = 0; i < numberOfContacts; ++i)
    {
        printf("find num: %s\n", namePhoneArray[i].phone);
        numberOfFindsInNum = findByNumber(sequenceOfNumbers, namePhoneArray[i].phone);
        numberOfFindsInStr = findByString(sequenceOfNumbers, namePhoneArray[i].phone);
        if (numberOfFindsInNum == strlen(sequenceOfNumbers) || numberOfFindsInStr == strlen(sequenceOfNumbers))
        {
            printf("find index: %d\n", namePhoneArray[i].index);
            arrayOfIndexes[counter] = namePhoneArray[i].index;
            counter++;
        }
    }
    return arrayOfIndexes;
}

int main(int argc, char *argv[])
{
    char c;
    int numberOfContacts;
    char *phoneNumber = argv[1];
    char *arrayOfIndexes;
    char arrayForIndexes[84];
    struct namePlusPhone namePhoneArray[42];
    numberOfContacts = readFile(namePhoneArray);
    arrayOfIndexes = find(phoneNumber, namePhoneArray, numberOfContacts, arrayForIndexes);
    for (int i = 0; i < strlen(arrayOfIndexes) - 1; ++i)
    {
        // printf("%s\n", namePhoneArray[i].name);
        // printf("%s\n", namePhoneArray[i].phone);
        // printf("%d\n", namePhoneArray[i].index);
        printf("Find index: %d\n", arrayOfIndexes[i]);
    }
}