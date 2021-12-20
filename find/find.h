#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * Colours line
 */
#define REDCOLOUR "\e[0;31m\033[1m"
#define GREENCOLOUR "\e[0;32m\033[1m"
#define YELLOWCOLOUR "\e[0;33m\033[1m"
#define BLUECOLOUR "\e[0;34m\033[1m"
#define PURPLECOLOUR "\e[0;35m\033[1m"
#define ENDCOLOUR "\033[0m\e[0m"

/**
 * Global variables
 */
regex_t regex;

/**
 * Show help for utility command find
 */
void helpCommand(char status);

/**
 * Find file with system calls
 */
char findFile(char *path, char *pattern, char status);

/**
 * Check file type
 */
char isDirectory(mode_t mode);

/**
 * Compare strings with regular expression
 */
char equalsRegex(char *pattern, char *chain);
