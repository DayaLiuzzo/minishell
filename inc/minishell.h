/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:22:12 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/11 19:45:09 by dliuzzo          ###   ########.fr       */
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

enum						token_type
{
	INREDIR,
	OUTREDIR,
	PIPE,
	SPACE_,
	TAB_,
	OPERATOR,
	APPOUTREDIR,
	HEREDOC,
	WORD
};

typedef struct s_utils
{
	int						i;
	int						j;
	int						start;
	int						varname_start;
	int						end;
	int 					varname_len;
	int						varcontent_len;
	int						varcontent_start;
	int						env_index;
}							t_utils;

typedef struct s_command_table
{
	char					**command;
	char					**infile;
	char					**outfile;
	char 					**env;
	struct s_command_table	*next;
}							t_command_table;

typedef struct s_input
{
	char					*linebuffer;
	size_t					nread;
	int						again;
	int						len;
}							t_input;

typedef struct s_lexbuf
{
	struct s_lexbuf			*next;
	struct s_lexbuf			*prev;
	char					*value;
	int						type;
}							t_lexbuf;

// PROGRAM
int							main(int ac, char **av, char **env);

// INIT STRUCT
void 						init_utils(t_utils *utils);
void						init_struct(t_input *input);

// FREE
void						ft_free(char *msg, t_input *input, t_lexbuf **tokens,
								int i);
void						ft_free_list(t_lexbuf **tokens);
void						ft_free_tab(char **value);

// TEST
void						print_stack(t_lexbuf *tokens);
void						print_tab(char **strs);

// LEXING
char						*fill_tokens(char *s, int i, t_lexbuf **tokens, t_input *input);
int							token_type(char *s, int *i);
int							token_context(t_input *input, t_lexbuf **tokens);
int 						precise_token(t_input *input, t_lexbuf **tmp, t_lexbuf **tokens, int type);
void						small_check(t_lexbuf **tokens, t_input *input);
void						quote_check(t_lexbuf **tokens, t_input *input);
void						big_check(char *s, int *size, t_lexbuf **tokens, t_input *input);
void						add_back(t_lexbuf **lst, t_lexbuf *new);
t_lexbuf					*new_tokens(char *s, int *i);
t_lexbuf					*token_recognition(char *s, t_input *input, int i, char **env);
t_lexbuf					*get_last(t_lexbuf *lst);
t_lexbuf					*ft_addprev(t_lexbuf *token);
t_lexbuf					*get_last(t_lexbuf *lst);
t_command_table				*create_command_table(t_lexbuf *tokens);

//EXPAND
int		find_envar(char *arg);
void	expand(t_lexbuf **tokens, t_input *input, char **env);
char *get_varname(char *value, t_input *input, t_lexbuf **tokens, t_utils *utils);
char *get_varcontent(char *value, t_input *input, t_lexbuf **tokens, t_utils *utils);
char *concatene_envar(char *value, char *envar, t_input *input, t_lexbuf** tokens, t_utils *utils);
char *get_envar(char *value, char **env, t_input *input, t_lexbuf **tokens, t_utils *utils);
char *expand_left(char *value, char *envar, t_input *input, t_lexbuf** tokens, t_utils *utils);
// REDIR
// void						ft_redir(t_lexbuf *tokens, t_lexbuf *head,
// 								t_split *split);
// void						ft_inredir(t_lexbuf *tokens, t_lexbuf *head,
// 								t_split *split);

// UTILS
int							is_space(char c);
void						skip(char *s, int *i, char del);
int	ft_strncmpp(char *s1, char *s2, int n);

#endif
