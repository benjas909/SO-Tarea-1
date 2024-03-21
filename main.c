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
  char lsCommand[64] = "ls "; // ls: muestra contenidos del directorio

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
  char mkdirCommand[64] = "mkdir "; // mkdir: crea una carpeta/directorio
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
  snprintf(copyCommand, sizeof(copyCommand), "cp ./Sprites/%c*.png ./Sprites/Alfabético/%s/", tolower(name[0]), name); // cp: copia un archivo a una ubicación dada
  system(copyCommand);
}

int main()
{

  system("cd Sprites/");

  const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

  int ind;

  char currLetter[2];
  currLetter[1] = '\0';

  if (!doesFolderExist("./Sprites/Alfabético/", sizeof("./Sprites/Alfabético/")))
  {
    system("mkdir ./Sprites/Alfabético/"); // mkdir: crea una carpeta en el directorio actual
  }

  for (ind = 0; ind < 26; ind++)
  {
    currLetter[0] = toupper(ALPHABET[ind]);
    // printf("%c\n", currLetter);
    char currFolder[64] = "./Sprites/Alfabético/";
    strcat(currFolder, currLetter);

    if (!doesFolderExist(currFolder, sizeof(currFolder)))
    {
      createFolder(currFolder, sizeof(currFolder));
    }

    copyFilesAZ(currLetter);
  }

  return 0;
}

// ls | grep -E "*_([1-9]|[1-9][0-9]|1[0-4][0-9]|15[0-1]).png" | xargs -i cp {} ./I/
// ls | grep -E "*_(15[2-9]|1[6-9][0-9]|2[0-4][0-9]|25[0-1]).png" // segunda generación
// ls | grep -E "*_(25[2-9]|2[6-9][0-9]|3[0-7][0-9]|38[0-6]).png" // tercera gen
// ls | grep -E "*_(38[7-9]|39[0-9]|4[0-8][0-9]|49[0-3]).png" // cuarta gen

// Las generaciones van desde los n´umeros 1-151 para la primera, 152-251 para la
// segunda, 252-386 para la tercera y 387-493 para la cuarta