#include <stdio.h>
#include <string.h>

struct namePlusPhone
{
    char name[101];
    char phone[101];
    int index;
};

int clearBuffer(char array[101]) // function for clearing buffer array in function readFile
{
    for (size_t i = 0; i <= 101; ++i) // for loop that erase data in every cell of array
        array[i] = 0;
}

char readFile(struct namePlusPhone arrayOfNamePlusPhone[100]) // function for reading every character from file with getChar function
{
    int ch;
    char bufferArray[101];

    int index = 0;
    int i = 0;

    while (1)
    {
        ch = getchar();

        if (ch == EOF) // checking end of file
        {
            break;
        }

        if (ch == '\n')
        {
            if (index % 2 == 0) // checking if line is name line
            {
                strcpy(arrayOfNamePlusPhone[index / 2].name, bufferArray); // copying buffer array to structure array as string on (index / 2) => data are structured such name is on every second line
                arrayOfNamePlusPhone[index / 2].index = (index / 2);
                i = 0;
                clearBuffer(bufferArray); // clearing buffer for new data
            }
            else
            {
                strcpy(arrayOfNamePlusPhone[(index - 1) / 2].phone, bufferArray);
                i = 0;
                clearBuffer(bufferArray); // clearing buffer for new data
            }
            index++;
        }
        else
        {
            if (ch >= 'A' && ch <= 'Z') // setting uppercase letters to lowercase
            {
                ch += 32;
            }
            bufferArray[i] = ch;
            i++;
        }
    }
    return index / 2; // returning number of contacts
}

int findByNumber(char *sequenceOfNumbers, char *phoneNumber) // function that takes sequence of numbers that we gave it when we enter a command plus phone number from arrayOfNamePlusPhone
{
    int find = 0;
    int counterSeqOFNum = 0;
    for (int counterPhoneNumber = 0; counterPhoneNumber < strlen(phoneNumber); counterPhoneNumber++) // looping through phone number
    {
        if (sequenceOfNumbers[counterSeqOFNum] == phoneNumber[counterPhoneNumber]) // checking if sequence number digit and phone number digit is same
        {
            counterSeqOFNum++;
            find++;
            // printf("Find num %d\n", strlen(sequenceOfNumbers));
            // printf("Finded num %d\n", counterSeqOFNum);
            // printf("findNum seq: %c, phoneN: %c\n", sequenceOfNumbers[counterSeqOFNum], phoneNumber[counterPhoneNumber]);
        }
        else // erasing progress if numbers dont match
        {
            find = 0;
            counterSeqOFNum = 0;
        }
        if (counterSeqOFNum == strlen(sequenceOfNumbers)) // checking if number of matching numbers is same length as sequence of numbers
        {
            return find;
        }
    }

    return -1;
}

int findByString(char *sequenceOfNumbers, char *costumerName) // function that takes sequence of numbers that we gave it when we enter a command plus costumerName and find if translated sequence of numbers to letters is in name
{
    int find = 0;
    int counterCostumerName = 0;
    int counterSeqOFNum = 0;
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

    int indexInArrayOfCharsReplInt;
    char *stringFromArrayOfCharsReplInt;

    for (counterCostumerName = 0; counterCostumerName < strlen(costumerName); counterCostumerName++) // looping through name
    {
        // making number from string
        if (sequenceOfNumbers[counterSeqOFNum] == 48)
        {
            indexInArrayOfCharsReplInt = 0; // index if it's zero
        }
        else
        {
            indexInArrayOfCharsReplInt = sequenceOfNumbers[counterSeqOFNum] - 49; // index
        }
        stringFromArrayOfCharsReplInt = arrayOfCharsReplInt[indexInArrayOfCharsReplInt]; // string on index saved in indexInArrayOfCharsReplInt
        // printf("str in arrayOfCharsReplInt: %d\n", indexInArrayOfCharsReplInt);

        if (find == strlen(sequenceOfNumbers))
        {
            return find;
        }
        for (int counterCharsReplInt = 0; counterCharsReplInt < strlen(stringFromArrayOfCharsReplInt); counterCharsReplInt++) // looping through string in arrayOfCharsReplInt
        {

            if (stringFromArrayOfCharsReplInt[counterCharsReplInt] == costumerName[counterCostumerName])
            {
                // printf("str in arrayOfCharsReplInt %c ==  costumerName %c\n", stringFromArrayOfCharsReplInt[counterCharsReplInt], costumerName[counterCostumerName]);
                // printf("costumerName %s\n", costumerName);
                find++;
                counterSeqOFNum++;
                break;
            }
            else
            {

                if (find > 0 && counterCharsReplInt == (strlen(stringFromArrayOfCharsReplInt) - 1))
                {
                    find = 0;
                    counterSeqOFNum = 0;
                }
            }
        }
    }

    return find;
}

char *find(char *sequenceOfNumbers, struct namePlusPhone namePhoneArray[100], int numberOfContacts, char arrayOfIndexes[100], int *indexCounter)
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
    struct namePlusPhone namePhoneArray[100];
    numberOfContacts = readFile(namePhoneArray);
    arrayOfIndexes = find(phoneNumberSequence, namePhoneArray, numberOfContacts, arrayForIndexes, indexCounter);

    for (int y = 0; y < numberOfContacts; ++y)
    {
        for (int i = 0; i < *indexCounter; ++i)
        {
            // printf("%d\n", *indexCounter);
            // printf("%d == %d\n", namePhoneArray[y].index, arrayOfIndexes[i]);
            if (arrayOfIndexes[i] == namePhoneArray[y].index)
            {
                printf("Name: %s\n", namePhoneArray[y].name);
                printf("Phone: %s\n", namePhoneArray[y].phone);
                printf("Index: %d\n", namePhoneArray[y].index);
            }
        }
    }
    return 0;
}