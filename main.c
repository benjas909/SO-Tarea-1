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
int doesFolderExist(char *name, size_t length)
{
  char lsCommand[64] = "ls ";

  strcat(lsCommand, name);
  strcat(lsCommand, " 2>> output.txt");

  int result = system(lsCommand) / 256;

  remove("output.txt");

  return !result;
}

/**
 * @brief Crea una carpeta con el nombre dado
 *
 * @param name
 * @param nameLen
 */
void createFolder(char *name, int nameLen)
{
  char mkdirCommand[9] = "mkdir ";
  strcat(mkdirCommand, name);

  system(mkdirCommand);
}

void copyFilesAZ(char *name)
{
  char copyCommand[64] = "";
  snprintf(copyCommand, sizeof(copyCommand), "cp Sprites/%c*.png %s/", tolower(name[0]), name);
  // printf("%s \n", copyCommand);
  system(copyCommand);
}

int main()
{

  const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

  int ind;

  char currLetter[2];
  currLetter[1] = '\0';

  for (ind = 0; ind < 26; ind++)
  {
    currLetter[0] = toupper(ALPHABET[ind]);
    // printf("%c\n", currLetter);

    if (!doesFolderExist(currLetter, 1))
    {
      createFolder(currLetter, 1);
    }

    copyFilesAZ(currLetter);
  }

  return 0;
}