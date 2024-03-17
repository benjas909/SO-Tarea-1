#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TMP_COMM_OUTPUT_FILE = "output.txt"

/**
 * @brief Retorna un string que contiene el directorio actual de trabajo
 *
 * @return const char*
 */
const char *currDir()
{
  system("pwd > output.txt");
  FILE *fptr = fopen("output.txt", "r");

  char *pwd = (char *)malloc(sizeof(char) * 100);
  if (pwd == NULL)
  {
    printf("Memoria no disponible.");
    exit(1);
  }

  if (fptr)
  {
    fgets(pwd, 100, fptr);
  }

  fclose(fptr);
  remove("output.txt");

  return pwd;
}

int main()
{
  printf("%s", currDir());

  return 0;
}