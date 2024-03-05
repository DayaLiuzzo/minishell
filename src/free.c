/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:45:18 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/05 15:26:46 by dliuzzo          ###   ########.fr       */
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
			if (tmp->value)
				free(tmp->value);
			free(tmp);
		}
	}
}

void ft_free(t_input *input, t_lexbuf *tokens, int leave)
{
    if(input->linebuffer)
    {
        free(input->linebuffer);
    }
	ft_free_list(tokens);
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

char **split_error(char **strs)
{
	int i;
	i = 0;
	printf("Fin\n");
	if(strs)
	{
		while(strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
	return (NULL);
}