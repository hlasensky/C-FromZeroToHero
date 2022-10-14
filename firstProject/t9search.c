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
    int ch;
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
                arrayOfNamePlusPhone[index / 2].index = (index / 2);
                i = 0;
                clearBuffer(bufferArray);
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
            if (ch >= 'A' && ch <= 'Z')
            {
                ch += 32;
            }
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
        // printf("findNum seq: %c, phoneN: %c\n", sequenceOfNumbers[counterSeqOFNum], phoneNumber[counterPhoneNumber]);
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

int findByString(char *sequenceOfNumbers, char *costumerName)
{
    int find;
    int counterCostumerName;
    find = 0;
    counterCostumerName = 0;
    char *arrayOfCharsReplInt[] = {
        "+",
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz"};

    int counterSeqOFNum = 0;
    int indexInArrayOfCharsReplInt;
    char *stringFromArrayOfCharsReplInt;

    for (counterCostumerName = 0; counterCostumerName < strlen(costumerName); counterCostumerName++) // looping through name
    {
        if (sequenceOfNumbers[counterSeqOFNum] == 48)
        {
            indexInArrayOfCharsReplInt = 0; // index
        }
        else
        {
            indexInArrayOfCharsReplInt = sequenceOfNumbers[counterSeqOFNum] - 49; // index
        }
        stringFromArrayOfCharsReplInt = arrayOfCharsReplInt[indexInArrayOfCharsReplInt]; // string on index saved in indexInArrayOfCharsReplInt
        // printf("str in arrayOfCharsReplInt: %d\n", indexInArrayOfCharsReplInt);

        for (int counterCharsReplInt = 0; counterCharsReplInt < strlen(stringFromArrayOfCharsReplInt); counterCharsReplInt++) // looping through string in arrayOfCharsReplInt
        {

            if (stringFromArrayOfCharsReplInt[counterCharsReplInt] == costumerName[counterCostumerName])
            {
                // printf("str in arrayOfCharsReplInt: %c == %c\n", stringFromArrayOfCharsReplInt[counterCharsReplInt], costumerName[counterCostumerName]);
                find++;
                break;
            }
            counterSeqOFNum++;
        }
        if (find == strlen(sequenceOfNumbers))
        {
            return find;
        }
    }

    return find;
}

char *find(char *sequenceOfNumbers, struct namePlusPhone namePhoneArray[42], int numberOfContacts, char arrayOfIndexes[42], int *indexCounter)
{

    int counter = 0;
    int numberOfFindsInNum;
    int numberOfFindsInStr;
    for (int i = 0; i < numberOfContacts; ++i)
    {
        // printf("find num: %s\n", namePhoneArray[i].phone);
        numberOfFindsInNum = findByNumber(sequenceOfNumbers, namePhoneArray[i].phone);
        numberOfFindsInStr = findByString(sequenceOfNumbers, namePhoneArray[i].name);
        if (numberOfFindsInNum == strlen(sequenceOfNumbers) || numberOfFindsInStr == strlen(sequenceOfNumbers))
        {
            //printf("find index: %d\n", namePhoneArray[i].index);
            arrayOfIndexes[counter] = namePhoneArray[i].index;
            counter++;
        }
    }
    *indexCounter = counter;
    return arrayOfIndexes;
}

int main(int argc, char *argv[])
{
    char c;
    int numberOfContacts;
    int arrayOfIndexesCounter = 0;
    int *indexCounter;
    char *phoneNumberSequence = argv[1];
    char *arrayOfIndexes;
    char arrayForIndexes[84];
    struct namePlusPhone namePhoneArray[42];
    numberOfContacts = readFile(namePhoneArray);
    arrayOfIndexes = find(phoneNumberSequence, namePhoneArray, numberOfContacts, arrayForIndexes, indexCounter);

    for (int y = 0; y < *indexCounter; ++y)
    {
        for (int i = 0; i < numberOfContacts; ++i)
        {
            //{printf("%d == %d\n", namePhoneArray[y].index, arrayOfIndexes[i]);
            if (arrayOfIndexes[i] == namePhoneArray[y].index)
            {
                printf("%d\n", *indexCounter);
                printf("Name: %s\n", namePhoneArray[y].name);
                printf("Phone: %s\n", namePhoneArray[y].phone);
                printf("Index: %d\n", namePhoneArray[y].index);
            }
        }
    }
    return 0;
}