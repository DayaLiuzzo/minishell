#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>
#include <errno.h>

typedef struct s_input
{
    char *linebuffer;
    size_t nread;
    int again;
    int len;
} t_input;

int main(int ac, char **av, char **env);
