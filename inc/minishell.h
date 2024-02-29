/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:22:12 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/02/29 16:59:41 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
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

}					t_lexbuf;

// PROGRAM

int					main(int ac, char **env);

// INIT

void				init_struct(t_input *input);
void				init_tokens(t_lexbuf *tokens);
void				build_tokens(t_lexbuf *tokens, t_input *input);
t_lexbuf			*ft_nexttoken(t_lexbuf *tokens, t_input *input, char *value);

// FREE
void				ft_free(t_input *input, t_lexbuf *tokens);
void				ft_free_list(t_lexbuf *tokens);

#endif
