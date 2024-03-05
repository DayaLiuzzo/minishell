/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:22:12 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/05 17:07:41 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
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
	char			*varname;
	struct s_args	*next;
}					t_args;

typedef struct s_input
{
	char			*linebuffer;
	size_t			nread;
	int				again;
	int				len;
}					t_input;

typedef struct s_split
{
	int				i;
	int				j;
	int				k;
	int				start;
	int				end;
	int				wordlen;
	int				word_count;
	int				squote;
	int				dquote;
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

int					main(int ac, char **av, char **env);

// INIT STRUCT

void				init_struct(t_input *input);
void				init_tokens(t_lexbuf *tokens);
void				init_split_count(t_split *split);
// FREE
void				ft_free(t_input *input, t_lexbuf *tokens, int i);
void				ft_free_list(t_lexbuf *tokens);
void				ft_free_tab(char **value);
char				**split_error(char **strs);

// TEST
void 				print_env(t_args *myenv);
void				print_stack(t_lexbuf *tokens);
void 				print_tab(char **strs);

// LEXING
void				analyse_token(t_lexbuf *input);
t_lexbuf			*build_tokens(t_input *input);
t_lexbuf			*ft_nexttoken(t_lexbuf *tokens, t_input *input,
						char *value);

// UTILS
char				**minishell_split(char *s);
char				*ft_malloc_words(t_split *split, char *s);
int					is_space(char c);
void				ft_double_loop(t_split *split, char *s);
void				ft_single_loop(t_split *split, char *s);

//ENV
t_args 				*get_env(char **env);
t_args 				*ft_next_env_var(t_args *args,char *value);
void 				ft_free_env(t_args *myenv);
void 				ft_error_env(char *msg, t_args *myenv);
#endif
