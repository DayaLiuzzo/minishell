/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:50:48 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/05 18:49:35 by dliuzzo          ###   ########.fr       */
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

void init_split_count(t_split *split)
{
    split->i = 0;
    split->dquote = 0;
    split->squote = 0;
    split->wordlen = 0;
}