#include "find.h"

int main(int argc, char *argv[]) {
  char verified = verifiedFlags(argc, argv);
  if (argc != 3 || verified) {
    if (argc == 2 && verified) {
      helpCommand();
      return EXIT_FAILURE;
    }
    status = 1;
    helpCommand();
    return EXIT_FAILURE;
  }
  findFile(argv[1], argv[2]);
  if (status == 0) {
    printf("%sEl patrón de búsqueda no se ha encontrado%s\n", PURPLECOLOUR,
           ENDCOLOUR);
  }
  printf("\n%s Se han encontrado %s%d%s %sarchivos y %s%d%s %scarpetas en la "
         "búsqueda %s\n",
         PURPLECOLOUR, GREENCOLOUR, amountFiles, ENDCOLOUR, PURPLECOLOUR,
         BLUECOLOUR, amountFolders, ENDCOLOUR, PURPLECOLOUR, ENDCOLOUR);
  return EXIT_SUCCESS;
}

char verifiedFlags(int size, char *args[]) {
  return size > 2
             ? ((strcmp(args[1], "-h") == 0 ||
                 strcmp(args[1], "--help") == 0) ||
                (strcmp(args[2], "-h") == 0 || strcmp(args[2], "--help") == 0))
             : (strcmp(args[1], "-h") == 0 || strcmp(args[1], "--help") == 0);
}

void helpCommand() {
  if (status == 0) {
    printf("%s./find%s  %s/path/to/file/ nameFileFind%s\n", PURPLECOLOUR,
           ENDCOLOUR, YELLOWCOLOUR, ENDCOLOUR);
    printf("\t%s/path/to/file/%s %sRuta o directorio donde desea empezar la "
           "búsqueda%s\n",
           YELLOWCOLOUR, ENDCOLOUR, BLUECOLOUR, ENDCOLOUR);
    printf("\t%snameFileFind%s   %sNombre del archivo a buscar%s\n",
           YELLOWCOLOUR, ENDCOLOUR, BLUECOLOUR, ENDCOLOUR);
  } else if (status == 1) {
    printf(
        "%sEspecifique un patrón de búsqueda válido. Ver ayuda -h o --help%s\n",
        REDCOLOUR, ENDCOLOUR);
  }
}

void findFile(char *path, char *pattern) {
  DIR *directory;
  struct dirent *content;
  struct stat fileStat;
  char *path2, *name2;

  directory = opendir(path);
  if (directory != NULL) {
    while ((content = readdir(directory))) {
      flagFolders = 0;
      if ((strcmp(content->d_name, ".") != 0) &&
          (strcmp(content->d_name, "..") != 0)) {
        name2 = content->d_name;
        path2 = malloc(strlen(path) + strlen(name2) + 2);
        strcpy(path2, path);
        if (!equalsRegex("/$", path2))
          strcat(path2, "/");
        strcat(path2, name2);
        stat(path2, &fileStat);
        mode_t mode = fileStat.st_mode;
        if (strstr(name2, pattern)) {
          status = 1;
          amountFiles++;
          ++flagFolders;
          isDirectory(mode) ? printf("%s%s%s\n", BLUECOLOUR, path2, ENDCOLOUR)
                            : printf("%s%s%s\n", GREENCOLOUR, path2, ENDCOLOUR);
        }
        if (isDirectory(mode)) {
          if (++flagFolders == 2) {
            amountFolders++;
            amountFiles--;
          }
          findFile(path2, pattern);
        }
      }
    }
  }
  closedir(directory);
}

char isDirectory(mode_t mode) { return S_ISDIR(mode); }

char equalsRegex(char *pattern, char *chain) {
  int request;
  regfree(&regex);
  request = regcomp(&regex, pattern, 0);
  if (request)
    return 0;
  request = regexec(&regex, chain, 0, NULL, 0);
  if (!request)
    return 1;
  return 0;
}
