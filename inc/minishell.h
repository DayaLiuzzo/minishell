/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:22:12 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/04 20:57:39 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_args
{
	char *varname;
	char *varcontent;
	struct s_args *next;
}	t_args;

typedef struct s_input
{
	char			*linebuffer;
	size_t			nread;
	int				again;
	int				len;
}					t_input;

typedef struct s_split
{
	int i;
	int j;
	int k;
	int len;
	int word_count;
	int squote;
	int dquote;
}					t_split;

typedef struct s_lexbuf
{
	t_args			*args;
	struct s_lexbuf	*next;
	char			*value;
	int				inredir;
	int				outredir;
	int				pipe;
	int				nl;
	int				variable;
	int				command;
	int				argument;
	int				heredoc;
	int				appoutredir;
	int				builtin;

}					t_lexbuf;

// PROGRAM

int					main(int ac, char **env);

// INIT STRUCT

void				init_struct(t_input *input);
void				init_tokens(t_lexbuf *tokens);
// FREE
void				ft_free(t_input *input, t_lexbuf *tokens, int i);
void				ft_free_list(t_lexbuf *tokens);
void				ft_free_tab(char **value);

// TEST
void 				print_stack(t_lexbuf *tokens);

// LEXING 
void 				analyse_token(t_lexbuf *input);
t_lexbuf    		*build_tokens(t_input *input);
t_lexbuf			*ft_nexttoken(t_lexbuf *tokens, t_input *input, char *value);

//UTILS
void minishell_split(char *s);
#endif
