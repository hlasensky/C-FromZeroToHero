#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int rce()
{
    int a, b, c, d;
    double x1, x2;
    printf("Zadej hodnutu a b c: ");
    scanf("%d %d %d", &a, &b, &c);
    d = b * b - 4 * a * c;
    if (d == 0)
    {
        x1 = (-b / (2 * a));
        printf("x1 = %f\n", x1);
    }
    else if (d < 0)
    {
        double i, r;
        r = (-b / (2 * a));
        i = (sqrt(-d) / (2 * a));
        printf("Komplex = %f + i%f\n", r, i);
    }
    else
    {
        x1 = (-b + sqrt(d) / (2 * a));
        x2 = (-b - sqrt(d) / (2 * a));
        printf("x1 = %f\n", x1);
        printf("x2 = %f\n", x2);
    }
}

int loop()
{
    int numberOfChar, numbers = 0, characters = 0, spec = 0;
    char symbols;
    printf("Zadej pocet znaku: ");
    scanf("%d", &numberOfChar);
    scanf("%c", &symbols); /*na49t8 enter aby ho odstranil*/
    printf("Zadej znaky: ");

    for (int i = 0; i < numberOfChar; i++)
    {
        scanf("%c", &symbols);
        printf("nacteny znak %c\n", symbols);
        if (symbols >= '0' && symbols <= '9')
        {
            numbers++;
        }
        else if (symbols >= 'a' && symbols <= 'z' || symbols >= 'A' && symbols <= 'Z')
        {
            characters++;
        }
        else
        {
            spec++;
        }
    }
    printf("Znaky %d\nCislice %d\nSpecialni %d", characters, numbers, spec);
}

int arr(void)
{
    int ls[5];
    int sum = 0, max;
    double average = 0;

    for (int i = 0; i < 5; ++i)
    {
        printf("Zadej cislo: \n");
        scanf("%d", &ls[i]);
    }

    max = ls[0];
    for (int i = 0; i < 5; ++i)
    {
        if (ls[i] > max)
        {
            max = ls[i];
        }
    }

    for (int s = 0; s < 5; ++s)
    {
        sum+= ls[s];
    }
    average = sum / 5;
    printf("Max: %d\n", max);
    printf("Sum: %d\n", sum);
    printf("Average: %f\n", average);
}

int main(void)
{
    /*rce()
    loop();*/

    arr();
}