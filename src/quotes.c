/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:44:06 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/15 18:33:28 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_removal(t_lexbuf **tokens, t_input *input)
{
	t_lexbuf	*current;
	char		*tmp;

	current = *tokens;
	while (current)
	{
		if (current->value && current->value[0] != '\0')
		{
			tmp = strdup(current->value);
			free(current->value);
			current->value = remove_quotes(tmp, tokens, input);
		}
		current = current->next;
	}
	if (!tokens)
		ft_free("alloc error quotes removal", input, tokens, 1);
}

char	*ft_join_quotes(char *src, char *new_str, int len)
{
	int	k;
	int	j;

	j = 0;
	k = 0;
	while (j < len)
	{
		if (src[k] == -34)
		{
			k++;
			while (j < len && src[k] != -34)
			{
				new_str[j] = src[k];
				j++;
				k++;
			}
			k++;
		}
		else if (src[k] == -39)
		{
			k++;
			while (j < len && src[k] != -39)
			{
				new_str[j] = src[k];
				j++;
				k++;
			}
			k++;
		}
		else
		{
			new_str[j] = src[k];
			j++;
			k++;
		}
	}
	new_str[j] = 0;
	return (new_str);
}

char	*remove_quotes(char *src, t_lexbuf **tokens, t_input *input)
{
	int		i;
	int		del;
	int		j;
	char	*new_str;

	j = 0;
	i = 0;
	del = 0;
	new_str = NULL;
	count_quotesrm(src, &i, &del);
	if (del == 0)
	{
		new_str = ft_strdup(src);
		return (new_str);
	}
	if ((new_str = (char *)malloc(sizeof(char) * (i + 1 - del))) == NULL)
		ft_free("Malloc Error at remove_quotes", input, tokens, 1);
	new_str = ft_join_quotes(src, new_str, i - del);
	return (new_str);
}

void	count_quotesrm(char *src, int *i, int *del)
{
	while (src[*i])
	{
		if (src[*i] == -34)
		{
			(*del)++;
			(*i)++;
			while (src[*i] && src[*i] != -34)
				(*i)++;
			(*del)++;
			(*i)++;
		}
		else if (src[*i] == -39)
		{
			(*del)++;
			(*i)++;
			while (src[*i] && src[*i] != -39)
				(*i)++;
			(*del)++;
			(*i)++;
		}
		else
			(*i)++;
	}
}
