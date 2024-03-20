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
  system("pwd > output.txt"); // pwd: muestra directorio actual
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
  char lsCommand[64] = "ls Sprites/"; // ls: muestra contenidos del directorio

  strcat(lsCommand, name);
  strcat(lsCommand, " 2>> output.txt"); // 2>> hace que el output del comando se envíe a un archivo output.txt

  int result = system(lsCommand) / 256; // por alguna razón, system devuelve los códigos de error multiplicados por 256

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
  char mkdirCommand[64] = "mkdir Sprites/"; // mkdir: crea una carpeta/directorio
  strcat(mkdirCommand, name);

  system(mkdirCommand);
}

/**
 * @brief Copia archivos por su primera letra a su carpeta correspondiente
 *
 * @param name
 */
void copyFilesAZ(char *name)
{
  char copyCommand[64] = "";
  snprintf(copyCommand, sizeof(copyCommand), "cp Sprites/%c*.png Sprites/%s/", tolower(name[0]), name); // cp: copia un archivo a una ubicación dada
  system(copyCommand);
}

int main()
{

  const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

  int ind;

  char currLetter[2];
  currLetter[1] = '\0';

  // if (!doesFolderExist("Sprites/Alfabético/", sizeof("Sprites/Alfabético/")))
  // {
  //   system("mkdir Sprites/Alfabético/");
  // }

  for (ind = 0; ind < 26; ind++)
  {
    currLetter[0] = toupper(ALPHABET[ind]);
    // printf("%c\n", currLetter);
    // char currFolder[64] = "Sprites/Alfabético";

    if (!doesFolderExist(currLetter, 1))
    {
      createFolder(currLetter, 1);
    }

    copyFilesAZ(currLetter);
  }

  return 0;
}