#include <stdio.h>
#include <stdlib.h>

struct date_t
{
    int year;
    int month;
    int day;
};

struct mereni_t
{
    struct date_t date;
    float temperature[377];
};

// funkce pro rozdeleni stringu s CSV na jednotlive udaje
int csv_get_item(char input[], char output[], int pos)
{
    int i = 0;
    if (input[pos] == ',')
    {
        pos++;
    }
    while (input[pos] != '\0' && input[pos] != ',')
    {
        output[i] = input[pos];
        pos++;
        i++;
    }
    output[i] = '\0';
    if (i == 0)
    {
        return -1;
    }
    else
    {
        return pos;
    }
}

void printArray(struct mereni_t mereniArray[377])
{
    for (int i = 0; i < 377; i++)
    {
        printf("%d\n", mereniArray[i].date.year);
        printf("%d\n", mereniArray[i].date.month);
        printf("%d\n", mereniArray[i].date.day);
        printf("%f\n", mereniArray[i].temperature[i]);
    }
}

float temperatureOfDay(struct date_t dat, struct mereni_t mereniArray[377])
{
    for (int i = 0; i < 377; i++)
    {
        if (mereniArray[i].date.year == dat.year && mereniArray[i].date.month == dat.month && mereniArray[i].date.day == dat.day)
        {
            printf("%f\n", mereniArray[i].temperature[i]);
        }
    }
}

int main()
{
    FILE *soubor;
    char filename[] = "B2BTUR01_max_teplota_2021.csv";
    char line[201];  // promenna pro radek souboru
    char outstr[10]; // promenna pro jeden udaj v radku
    int n;
    int k;
    int den;
    int rok;
    int mesic;
    struct mereni_t mereniArray[377];

    // vcetne pole pro vsevhna mereni

    soubor = fopen(filename, "r");

    if (soubor != NULL)
    {
        n = 0; // celkove pocitadlo mereni
        while (fscanf(soubor, "%200s", line) != EOF)
        {

            k = 0;
            den = 1;
            printf("Nacteny string: '%s'\n", line);

            k = csv_get_item(line, outstr, k); // nactete udaj z radku vstupu (rok)

            printf("%s\n", outstr); // kontrolni vytisteni nactene casti stringu

            rok = atoi(outstr);

            k = csv_get_item(line, outstr, k);
            printf("%s\n", outstr); // kontrolni vytisteni nactene casti stringu

            mesic = atoi(outstr);

            while (k != -1)
            {
                mereniArray[n].date.year = rok;
                mereniArray[n].date.month = mesic;
                mereniArray[n].date.day = den;
                k = csv_get_item(line, outstr, k);
                float mer = atof(outstr);
                mereniArray[n].temperature[n] = mer;
                // printf("%f\n", mereniArray[n].temperature[den - 1]);

                n++; // pocitadlo mereni
                den++;

                // nacist dalsi polozku z radky souboru -- zmeni se k ktere restujeme ve while
            }
            puts("Hi");
        }
        fclose(soubor);
    }
    printf("celkem nacteno mereni: %d\n", n);

    printf("Tak a koncime!\n");
    // printArray(mereniArray);
    struct date_t dat;
    dat.year = 2021;
    dat.month = 7;
    dat.day = 5;
    temperatureOfDay(dat, mereniArray);
    return 0;
}
