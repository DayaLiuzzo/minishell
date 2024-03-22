/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:22:12 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/22 16:07:19 by dliuzzo          ###   ########.fr       */
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

enum				e_token_type
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
	int				i;
	int				j;
	int				start;
	int				varname_start;
	int				end;
	int				varname_len;
	int				varcontent_len;
	int				varcontent_start;
	int				env_index;
	char			*varname1;
	char			*varcontent1;
}					t_utils;

typedef struct s_input
{
	char			*linebuffer;
	size_t			nread;
	int				again;
	int				len;
}					t_input;

typedef struct s_lexbuf
{
	struct s_lexbuf	*next;
	struct s_lexbuf	*prev;
	char			*value;
	char			**env;
	int				type;
	t_input			*input;
}					t_lexbuf;

// PROGRAM
int					main(int ac, char **av, char **env);

// INIT STRUCT
void				init_utils(t_utils *utils);
void				init_struct(t_input *input);
void				reset_iterators(t_utils *utils);

// FREE
void				ft_free(char *msg, t_lexbuf **tokens, int i);
void				ft_free_list(t_lexbuf **tokens);
void				ft_free_tab(char **value);
void				ft_free_str(char *s);

// TEST
void				print_stack(t_lexbuf *tokens);
void				print_tab(char **strs);

// LEXING
char				*fill_tokens(char *s, int i, t_lexbuf **tokens);
int					token_type(char *s, int *i);
int					token_context(t_lexbuf **tokens);
int					token_check(t_lexbuf *tmp, t_lexbuf **tokens);
int					precise_token(t_lexbuf **tmp, t_lexbuf **tokens, int type);
void				small_check(t_lexbuf **tokens, int i);
void				quote_check(t_lexbuf **tokens);
void				big_check(char *s, int *size, t_lexbuf **tokens);
void				add_back(t_lexbuf **lst, t_lexbuf *new);
t_lexbuf			*new_tokens(char *s, int *i, t_input *input);
t_lexbuf			*token_recognition(char *s, t_input *input, int i,
						char **env);
t_lexbuf			*get_last(t_lexbuf *lst);
t_lexbuf			*ft_addprev(t_lexbuf *token);
t_lexbuf			*get_last(t_lexbuf *lst);
t_lexbuf			*parsing(t_input *input, char **env);

// EXPAND
int					find_envar(char *arg, int i);
void				expand(t_lexbuf **tokens, char **env);
char				*get_varname(char *value, t_lexbuf **tokens, t_utils *utils,
						int j);
char				*get_varcontent(char *value, t_lexbuf **tokens,
						t_utils *utils, char *s);
char				*concatene_envar(char *value, char *envar,
						t_lexbuf **tokens, t_utils *utils);
char				*get_envar(char *value, char **env, t_lexbuf **tokens,
						t_utils *utils);
char				*expand_left(char *value, char *envar, t_lexbuf **tokens,
						t_utils *utils);
t_lexbuf			*create_tmp_list(char **new_strs, t_lexbuf *tmp,
						t_lexbuf **tokens, t_input *input);
t_lexbuf			*new_tokens_pexpand(char *s, int type, t_lexbuf **tokens,
						t_input *input);
t_lexbuf			*split_expands(t_lexbuf **tokens, t_input *input);
void				do_expansion(t_lexbuf *tmp, t_lexbuf **tokens, char **env,
						t_utils *utils);
t_lexbuf			*remove_emptyexpands(t_lexbuf **tokens);
// QUOTES
char				*remove_quotes(char *src, t_lexbuf **tokens);
void				count_quotesrm(char *src, int *i, int *del);
void				quotes_removal(t_lexbuf **tokens);
char				*ft_join_quotes(char *src, char *new_str, int len);
void				skip_dquotes(t_utils *utils, char *src, int len,
						char *new_str);
void				skip_squotes(t_utils *utils, char *src, int len,
						char *new_str);
void				skip_check(char *value, int *i, int *inquote, char del);
// UTILS
int					is_space(char c);
void				skip(char *s, int *i, char del);
int					ft_strncmpp(char *s1, char *s2, int n);
int					strncmp_env(char *s1, char *s2, int n);
void				negate_quotes(t_lexbuf **tokens);
int					is_indquote(char *s, t_utils *utils);
void				pos_quotes(t_lexbuf **tokens);
char				*mark_empty_expand(t_lexbuf **tokens);
t_lexbuf			*copy_tokens(t_lexbuf **tokens, t_lexbuf *current);

#endif
