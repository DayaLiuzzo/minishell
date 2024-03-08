/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:45:18 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/08 17:06:34 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_list(t_lexbuf **tokens)
{
	t_lexbuf	*tmp;

	if (*tokens)
	{
		tmp = *tokens;
		while (*tokens)
		{
			tmp = *tokens;
			*tokens = (*tokens)->next;
			if (tmp->value)
				free(tmp->value);
			free(tmp);
		}
	}
}

void ft_free(char *msg, t_input *input, t_lexbuf **tokens, int leave)
{
	if(msg)
		printf("%s\n", msg);
    if(input->linebuffer)
	{
			free(input->linebuffer);
			input->linebuffer = NULL;
	}
	ft_free_list(tokens);
	tokens = NULL;
	if(leave == 1)
		exit(1);
}

void	ft_free_tab(char **value)
{
	int	i;

	if (value)
	{
		i = 0;
		while (value[i])
		{
			free(value[i]);
			i++;
		}
		free(value);
	}
}
