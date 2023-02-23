#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

enum { dead, alive };

void  print_matrix(char *m, const int ml, const int mc)
{
  for(int i = 0; i < mc+2; i++)
    printf("--");
  printf("\n");
  for(int i = 0; i < ml; i++)
    {
      printf("|");
      for(int j = 0; j < mc; j++)
        {
          if(*(m + i*mc + j)) // == m[i][j]
            printf("\033[105m  \033[0m");
          else
            printf("  ");
        }
      printf("  |\n");
    }
  for(int i = 0; i < mc+2; i++)
    printf("--");
  printf("\n");
}

char  update_cell(char *m, const int ipos, const int jpos, const int ml, const int mc)
{
  int  nb = 0;
  int  i, j;
  for (i = ipos - 1; i <= ipos+1; i++)
    {
      if (i >= 0 && i < ml)
      {
        for(j = jpos-1; j <= jpos+1; j++)
          {
            if (j >= 0 && j < mc)
            {
              if (i != ipos || j != jpos)
              {
                if (*(m + i * mc + j) == alive)
                {
                  nb++;
                }
              }
            }
          }
      }
    }
  if (*(m + ipos * mc + jpos) == alive)
  {
    if(nb == 2 || nb == 3)
      return alive;
    else
      return dead;
  }
  else
  {
    if (nb == 3)
      return alive;
    else
      return dead;
  }
}

void  updateV1(char *m, char *bis, const int ml, const int mc)
{
  for(int i = 0; i < ml; i++)
    {
      for(int j = 0; j < mc; j++)
        {
          *(bis + i * mc + j) = update_cell(m, i, j, ml, mc);
        }
    }
  for(int i = 0; i < ml; i++)
      for(int j = 0; j < mc; j++)
          *(m + i * mc + j) = *(bis + i * mc + j);
}

void  set_matrix(char *m, const int ml, const int mc, char *s, const int sl, const int sc, const int x, const int y)
{
  for(int i = y; i < y+sl; i++)
      for(int j = x; j < x+sc; j++)
          *(m + i * mc + j) = *(s + (i-y) * sc + (j-x));
}

int main(void)
{
  const  int  ml = 20;
  const  int  mc = 30;
  
  char  matrix[20][30] = {dead};
  char  bis[20][30] = {dead};
  char  s[7][5] = { {0, 0, 0, 1, 1}, {0, 0, 1, 0, 1}, {0, 1, 1, 1, 0}, {1, 1, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 1}, {0, 0, 0, 1, 1} };
  set_matrix(&matrix[0][0], ml, mc, &s[0][0], 7, 5, 10, 6);

  while (1)
    {
      system("clear"); // cls on windows
      updateV1(&matrix[0][0], &bis[0][0], ml, mc);
      print_matrix(&matrix[0][0], ml, mc);
      usleep(200000);
    }
  return 0;
}
