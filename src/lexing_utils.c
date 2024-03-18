/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:24:06 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/18 18:22:23 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexbuf	*new_tokens(char *s, int *i, t_input *input)
{
	t_lexbuf	*new;

	new = malloc(sizeof(t_lexbuf));
	if (new == NULL)
		return (NULL);
	new->value = NULL;
	new->input = input;
	new->type = token_type(s, i);
	new->next = NULL;
	return (new);
}

void	quote_check(t_lexbuf **tokens)
{
	t_lexbuf	*tmp;
	int			i;
	int			inquote;

	i = 0;
	inquote = 2;
	tmp = *tokens;
	tmp = get_last(tmp);
	while (tmp && tmp->value[i])
	{
		if (tmp->value[i] == '"')
		{
			inquote++;
			skip(tmp->value, &i, '"');
			if (tmp->value[i] == '"')
			{
				i++;
				inquote++;
			}
		}
		else if (tmp->value[i] == '\'')
		{
			inquote++;
			skip(tmp->value, &i, '\'');
			if (tmp->value[i] == '\'')
			{
				i++;
				inquote++;
			}
		}
		else
			i++;
	}
	if (inquote % 2 == 0)
		return ;
	printf("tmp -> %s\ninquote ->%i\n", tmp->value, inquote);
	ft_free("Quotes fucked up", tokens, 0);
}

int	token_context(t_lexbuf **tokens)
{
	t_lexbuf	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == INREDIR)
		{
			if (precise_token(&tmp, tokens, INREDIR) == 0)
				return (0);
		}
		else if (tmp->type == OUTREDIR)
		{
			if (precise_token(&tmp, tokens, OUTREDIR) == 0)
				return (0);
		}
		else if (tmp->type == HEREDOC)
		{
			if (precise_token(&tmp, tokens, HEREDOC) == 0)
				return (0);
		}
		else if (tmp->type == APPOUTREDIR)
		{
			if (precise_token(&tmp, tokens, APPOUTREDIR) == 0)
				return (0);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

int	precise_token(t_lexbuf **tmp, t_lexbuf **tokens, int type)
{
	t_lexbuf	*current;

	current = *tmp;
	if (tmp)
	{
		if (!(*tmp)->next)
			return (0);
		else if ((*tmp)->next->type != WORD)
			return (0);
		else
		{
			(*tmp)->type = type;
			free((*tmp)->value);
			(*tmp)->value = NULL;
			(*tmp)->value = ft_strdup((*tmp)->next->value);
			if (!(*tmp)->value)
				ft_free("Alloc Error at ft_inredir", tokens, 1);
			current = current->next;
			(*tmp)->next = (*tmp)->next->next;
			free(current->value);
			free(current);
			return (1);
		}
	}
	return (0);
}

t_lexbuf	*ft_addprev(t_lexbuf *token)
{
	t_lexbuf	*tmp;
	t_lexbuf	*tmp2;

	if (token)
	{
		token->prev = NULL;
		tmp = token;
		tmp2 = token->next;
		while (tmp && tmp2)
		{
			tmp2->prev = tmp;
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
	}
	return (token);
}
