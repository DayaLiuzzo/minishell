/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:52 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/02/29 17:08:51 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    build_tokens(t_lexbuf *tokens, t_input *input)
{
    int i;
    char **values;
    t_lexbuf *ea;
    
    ea = NULL;
    tokens = NULL;
    i = 0;
    values = ft_split(input->linebuffer, ' ');
    while (values[i] != NULL)
		i++;
	i = i - 1;
	while (i >= 1)
	{
		ea = ft_nexttoken(tokens, input, values[i]);
		ea->next = tokens;
		tokens = ea;
		i--;
	}
        printf("token->value ----->%s\n", tokens->value);
        // tokens = tokens->next;
}