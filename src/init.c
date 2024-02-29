/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:50:48 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/02/29 16:18:33 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_struct(t_input *input)
{
    input->nread = 0;
    input->again = 1;
    input->len = 0;
    input->linebuffer = NULL;
}
void init_tokens(t_lexbuf *tokens, t_input *input)
{
    tokens->next = ft_nexttoken(tokens, input);
    tokens->prev = ft_prevtoken(tokens, input);
    tokens->inredir = 0;
    tokens->outredir = 0;
    tokens->pipe = 0;
    tokens->nl = 0;
    tokens->variable = 0;
    tokens->command = 0;
    tokens->argument = 0;
}

t_lexbuf *ft_nexttoken(t_lexbuf *tokens, t_input *input)
{
	t_lexbuf *new;

	new = (t_lexbuf *)malloc(sizeof(t_lexbuf));
	if (!new)
		ft_free(input, tokens);
	new->next = NULL;
	return (new);
}

t_lexbuf *ft_prevtoken(t_lexbuf *tokens, t_input *input)
{
	t_lexbuf *new;

	new = (t_lexbuf *)malloc(sizeof(t_lexbuf));
	if (!new)
		ft_free(input, tokens);
	new->prev = NULL;
	return (new);
}