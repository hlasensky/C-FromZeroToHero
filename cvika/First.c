#include <stdio.h>

int pdm()
{
  int a, b, c, d;
  printf("Zadej hodnutu a: ");
  scanf("%d", &a);
  printf("Zadej hodnutu b: ");
  scanf("%d", &b);
  printf("Zadej hodnutu c: ");
  scanf("%d", &c);
  d = b * b - 4 * a * c;
  if (d < 0)
  {
    printf("Řešení bude komplexní!\n");
  }
  else
  {
    printf("Řešní bude reálné!\n");
  };
  printf("Value of discriminant is %d\n", d);
  return d;
};

int modulo(valueOfd)
{
  if (valueOfd % 2 == 0)
  {
    printf("Je sudý\n");
  }
  else
  {
    printf("Je lichý\n");
  };
  return 0;
};

int interval(min, max, value)
{
  if (min < value && max > value)
  {
    printf("Patří");
  }
  else
  {
    printf("Nepatří");
  }
  return 0;
}

int interval2D(minX, maxX, minY, maxY, value)
{
  if (minX < value && minY > value && maxX < value && maxY > value)
  {
    printf("Patří");
  }
  else
  {
    printf("Nepatří");
  }
  return 0;
}

int prestupnyRok(rok)
{
  if (rok % 2 == 0)
  {
    if (rok % 100 == 0)
    {
      if (rok % 400 == 0)
      {
        printf("Rok je přestupny.\n");
      }
      else
      {
        printf("Rok je nepřestupný.\n");
      }
    }
    else
    {
      printf("Rok je přestupny.\n");
    }
  }
  else
  {
    printf("Rok je nepřestupny.\n");
  }
};

int main()
{
  /*int valueOfd = pdm();
  interval2D(min, max, minY, maxY, tValue);
  modulo(valueOfd);*/
  int min = 3, max = 16, minY = 30, maxY = 19, tValue = 5, fValue = 85;
  interval(min, max, fValue);
}