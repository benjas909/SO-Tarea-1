#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

/**
 * @brief Revisa si la carpeta de nombre @name existe, retorna 1 si existe, 0 si no.
 *
 * @param name
 * @return int
 */
int doesFolderExist(char name)
{

  char lsCommand[5] = "ls x";

  lsCommand[3] = name;

  int result = system(lsCommand) / 256;

  return !result;
}

int main()
{

  const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
  // printf("%s", currDir());

  int ind;

  char currLetter;

  for (ind = 0; ind < 26; ind++)
  {
    currLetter = toupper(ALPHABET[ind]);
    // printf("%c\n", currLetter);

    printf("%d\n", doesFolderExist(currLetter));
  }

  return 0;
}