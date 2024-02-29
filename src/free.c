/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:45:18 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/02/29 16:18:03 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_list(t_lexbuf *tokens)
{
	t_lexbuf	*tmp;

	if (tokens)
	{
		tmp = tokens;
		while (tokens)
		{
			tmp = tokens;
			tokens = tokens->next;
			free(tmp);
		}
	}
}

void ft_free(t_input *input, t_lexbuf *tokens)
{
    if(input->linebuffer)
    {
        free(input->linebuffer);
        input->linebuffer = NULL;
    }
    if (tokens)
        ft_free_list(tokens);
    printf("ERROR\n");
	exit(1);
}