#include "find.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
  char status = 0;
  if (argc != 3) {
    if(argc == 2) {
      if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) helpCommand(0);
      else helpCommand(1);
    } else {
      helpCommand(1);
    }
    return EXIT_FAILURE;
  }
  status = findFile(argv[1], argv[2], status);
  if (status == 0) {
    printf("%sEl patron de busqueda no se ha encontrado%s\n", PURPLECOLOUR, ENDCOLOUR);
  } 
  return EXIT_SUCCESS;
}

void helpCommand(char status){
  if (status == 0) {
    printf("%s./find%s  %s/path/to/file/ nameFileFind%s\n", PURPLECOLOUR, ENDCOLOUR, YELLOWCOLOUR, ENDCOLOUR);
    printf("\t%s/path/to/file/%s %sRuta o directorio donde desea empezar la busqueda%s\n", YELLOWCOLOUR, ENDCOLOUR, BLUECOLOUR, ENDCOLOUR);
    printf("\t%snameFileFind%s   %sNombre del archivo a buscar%s\n", YELLOWCOLOUR, ENDCOLOUR, BLUECOLOUR, ENDCOLOUR);
  } else if (status == 1) {
    printf("%sEspecifique un patron de busqueda. Ver ayuda -h o --help%s\n", REDCOLOUR, ENDCOLOUR);
  }
}

char findFile(char *path, char *pattern, char status){
  DIR *directory;
  struct dirent *content;
  struct stat fileStat;
  char *path2, *name2;

  directory = opendir(path);
  if (directory != NULL){
    while ((content = readdir(directory))) {
      if ((strcmp(content->d_name, ".") != 0) && (strcmp(content->d_name, "..") != 0)) {
        name2 = content->d_name;
        path2 = malloc(strlen(path) + strlen(name2) + 2);
        strcpy(path2, path);
        if (!equalsRegex("/$", path2)) strcat(path2, "/");
        strcat(path2, name2);
        stat(path2, &fileStat);
        mode_t mode = fileStat.st_mode;
        if (strstr(name2, pattern)) { 
          status = 1;
          printf("%s%s%s\n", GREENCOLOUR, path2, ENDCOLOUR);
        }
        if (isDirectory(mode)) { 
          status = findFile(path2, pattern, status);
        }   
      }
    }
  }
  closedir(directory);
  return status;
}

char isDirectory(mode_t mode){
  if (S_ISDIR(mode)) return 1;
  return 0;
}

char equalsRegex(char *pattern, char *chain){
  int request;
  regfree(&regex);
  request = regcomp(&regex, pattern, 0);
  if (request) return 0;
  request = regexec(&regex, chain, 0, NULL, 0);
  if (!request) return 1;
  return 0;
}
