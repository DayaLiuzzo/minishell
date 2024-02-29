/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:22:12 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/02/29 15:26:11 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_lexbuf
{
    struct s_stack *next;
    struct s_stack *prev;
    char *value;
    int redirect;
    int 
} t_lexbuf;

int     main(int ac, char **env);
void    init_struct(t_input *input);

#endif
