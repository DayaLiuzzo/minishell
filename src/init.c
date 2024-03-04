/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:50:48 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/04 21:07:55 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_struct(t_input *input)
{
    input->nread = 0;
    input->again = 1;
    input->len = 0;
    // input->linebuffer = NULL;
}
void init_tokens(t_lexbuf *tokens)
{
    tokens->inredir = 0;
    tokens->outredir = 0;
    tokens->pipe = 0;
    tokens->nl = 0;
    tokens->variable = 0;
    tokens->command = 0;
    tokens->argument = 0;
    tokens->args = NULL;
	tokens->next = NULL;
	tokens->value = NULL;
	tokens->heredoc = 0;
	tokens->appoutredir = 0;
	tokens->builtin = 0;
}

t_lexbuf *ft_nexttoken(t_lexbuf *tokens, t_input *input, char *value)
{
	t_lexbuf *new;
    
    
	new = (t_lexbuf *)malloc(sizeof(t_lexbuf));
	if (!new)
		ft_free(input, tokens, 1);
    init_tokens(new);
	new->value = ft_strdup(value);
    if(new->value == NULL)
        ft_free(input, tokens, 1);
    new->next = NULL;
    
	return (new);
}