/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:52 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/04 21:17:06 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexbuf    *build_tokens(t_input *input)
{
    int i;
    char **values;
    t_lexbuf *ea;
	t_lexbuf *token;
    
    ea = NULL;
	token = NULL;
    i = 0;
    values = ft_split(input->linebuffer, ' ');
    while (values[i] != NULL)
		i++;
	i = i - 1;
	while (i >= 0)
	{
		ea = ft_nexttoken(token, input, values[i]);
		ea->next = token;
		token = ea;
		i--;
	}
	ft_free_tab(values);
	// print_stack(token);
	return (token);
}

void analyse_token(t_lexbuf *tokens)
{
	t_lexbuf *tmp;
	tmp = tokens;

	while(tmp)
	{
		
	}
	
}