#include <stdio.h>
#include <string.h>

int error = 0;
const int arraySizeContacts = 100;
const int rowSize = 101;

struct namePlusPhone // structure for contact
{
    char name[rowSize];
    char phone[rowSize];
    int index;
};

// help functions
int clearBuffer(char array[rowSize]) // function for clearing buffer array in function readFile
{
    for (size_t i = 0; i <= rowSize; ++i) // for loop that erase data in every cell of array
        array[i] = 0;
}

int controlOfInput(char *sequenceOfChars, char *errorMessage) // function that check if the input is a number
{
    for (int index = 0; index < strlen(sequenceOfChars); index++)
    {
        // printf("%c\n", sequenceOfChars[index]);
        if (sequenceOfChars[index] < 48 || sequenceOfChars[index] > 57)
        {
            printf("%s\n", errorMessage);
            return 1;
        }
    }
    return 0;
}
//-------------------------------------

char readFile(struct namePlusPhone arrayOfNamePlusPhone[100]) // function for reading every character from file with getChar function
{
    int index = 0;
    int charCounter = 0;
    int error = 0;
    int ch;
    char bufferArray[rowSize];
    char errorMessage[] = "Phone numbers must be in every other row!";
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
                charCounter = 0;
                clearBuffer(bufferArray); // clearing buffer for new data
            }
            else
            {
                char str[rowSize];
                strcpy(str, bufferArray);
                error = controlOfInput(str, errorMessage);

                if (error) // checking if function controlOfInput returns an error
                {
                    return -1;
                }
                strcpy(arrayOfNamePlusPhone[(index - 1) / 2].phone, bufferArray);
                charCounter = 0;
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
            bufferArray[charCounter] = ch;
            charCounter++;
        }
    }
    if (index % 2 == 0)
    {
        return index / 2; // returning number of contacts
    }
    printf("Enter Names and Phone numbers!\n");
    return -1;
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
            // printf("Found num %d\n", counterSeqOFNum);
            // printf("findNum seq: %c, phoneN: %c\n", sequenceOfNumbers[counterSeqOFNum], phoneNumber[counterPhoneNumber]);
        }
        else // erasing progress if numbers dont match
        {
            find = 0;
            counterSeqOFNum = 0;
        }
        if (counterSeqOFNum == strlen(sequenceOfNumbers)) // checking if number of matching numbers is same length as sequence of numbers
        {
            return 0;
        }
    }
    return 1;
}

int findByString(char *sequenceOfNumbers, char *costumerName) // function that takes sequence of numbers that we gave it when we enter a command plus costumerName and find if translated sequence of numbers to letters is in name
{
    int find = 0;
    int counterCostumerName = 0;
    int counterSeqOFNum = 0;
    int indexInArrayOfCharsReplInt;
    char *stringFromArrayOfCharsReplInt;
    char *arrayOfCharsReplInt[] = {
        "+",
        "",
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz"}; // array representing numbers in sequence of numbers (number in sequenceOfNumbers - 1 = index in array)

    for (counterCostumerName = 0; counterCostumerName <= strlen(costumerName); counterCostumerName++) // looping through costumer name
    {
        // making from sequence of numbers(type char) numbers(type int)
        if (sequenceOfNumbers[counterSeqOFNum] == 48) // checking if number is zero
        {
            indexInArrayOfCharsReplInt = 0;
        }
        else
        {
            indexInArrayOfCharsReplInt = sequenceOfNumbers[counterSeqOFNum] - 48; // checking if number is different from zero
        }

        stringFromArrayOfCharsReplInt = arrayOfCharsReplInt[indexInArrayOfCharsReplInt]; // string on index indexInArrayOfCharsReplInt saved in stringFromArrayOfCharsReplInt
        // printf("str in arrayOfCharsReplInt: %d\n", indexInArrayOfCharsReplInt);

        if (find == strlen(sequenceOfNumbers))
        {
            return 0;
        }
        for (int counterCharsReplInt = 0; counterCharsReplInt < strlen(stringFromArrayOfCharsReplInt); counterCharsReplInt++) // looping through string in arrayOfCharsReplInt
        {
            if (stringFromArrayOfCharsReplInt[counterCharsReplInt] == costumerName[counterCostumerName]) // checking if character is in costumer name
            {
                //printf("str in arrayOfCharsReplInt %c ==  costumerName %c\n", stringFromArrayOfCharsReplInt[counterCharsReplInt], costumerName[counterCostumerName]);
                // printf("costumerName %s\n", costumerName);
                find++;
                counterSeqOFNum++;
                break;
            }
            else
            {
                if (find > 0 && counterCharsReplInt == (strlen(stringFromArrayOfCharsReplInt) - 1)) // checking if next character is match if not reset
                {
                    find = 0;
                    counterSeqOFNum = 0;
                }
            }
        }
    }

    return 1;
}

char *find(char *sequenceOfNumbers, struct namePlusPhone namePhoneArray[100], int numberOfContacts, char arrayForIndexes[200], int *indexCounter) // function that goes through all the contacts and passes them to the findByNumber and findByString functions and tracks when the functions find match
{
    int counter = 0;
    int numberOfFindsInNum;
    int numberOfFindsInStr;
    for (int i = 0; i < numberOfContacts; ++i)
    {
        // printf("find num: %s\n", namePhoneArray[i].phone);
        numberOfFindsInNum = findByNumber(sequenceOfNumbers, namePhoneArray[i].phone);
        numberOfFindsInStr = findByString(sequenceOfNumbers, namePhoneArray[i].name);
        if (!numberOfFindsInNum || !numberOfFindsInStr) // checking if aether of the functions found a match
        {
            // printf("found index: %d\n", namePhoneArray[i].index);
            arrayForIndexes[counter] = namePhoneArray[i].index; // saving index of found contact to an array
            counter++;
        }
    }

    *indexCounter = counter; // saving number of found contacts
    return arrayForIndexes;
}

int main(int argc, char *argv[])
{
    char c;
    int numberOfContacts;
    int arrayOfIndexesCounter;
    int indexCounter;
    char *phoneNumberSequence = argv[1];
    char *arrayOfIndexes;
    char arrayForIndexes[200];
    char errorMessage[] = "As an argument please enter number or numbers for example 11 or 602!";
    struct namePlusPhone namePhoneArray[100]; // making array of structures
    indexCounter = 0;

    numberOfContacts = readFile(namePhoneArray);

    if (argc > 1) // check if the program gets an argument
    {
        error = controlOfInput(phoneNumberSequence, errorMessage);

        if (error || numberOfContacts == -1) // checking if function controlOfInput returns an error
        {
            return 1;
        }
        arrayOfIndexes = find(phoneNumberSequence, namePhoneArray, numberOfContacts, arrayForIndexes, &indexCounter);

        if (indexCounter != 0) // checking if there is a found contact
        {
            for (int y = 0; y < numberOfContacts; ++y) // printing a result
            {
                for (int i = 0; i < indexCounter; ++i)
                {
                    // printf("%d\n", *indexCounter);
                    // printf("%d == %d\n", namePhoneArray[y].index, arrayOfIndexes[i]);
                    if (arrayOfIndexes[i] == namePhoneArray[y].index)
                    {
                        printf("%s, %s\n", namePhoneArray[y].name, namePhoneArray[y].phone);
                    }
                }
            }
        }
        else
        {
            printf("Contact(s) not found");
        }
        return 0;
    }

    for (int y = 0; y < numberOfContacts; ++y) // printing full list of contacts because the program did't get an argument
    {
        printf("%s, %s\n", namePhoneArray[y].name, namePhoneArray[y].phone);
    }
    return 0;
}