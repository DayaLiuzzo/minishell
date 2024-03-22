/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:52 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/22 18:04:06 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexbuf	*token_recognition(char *s, t_input *input, int i, char **env)
{
	t_lexbuf	*tokens;
	t_lexbuf	*tmp;

	tokens = NULL;
	tmp = NULL;
	while ((size_t)i < ft_strlen(s))
	{
		while (s[i] && (is_space(s[i]) == 1))
			i++;
		if (s[i] && (is_space(s[i]) == 0))
		{
			tmp = new_tokens(s, &i, input);
			if (tmp == NULL)
				ft_free("Alloc Failure in new_tokens", &tokens, 1);
			big_check(&s[i], &i, &tmp);
			if (tmp->value[0])
				add_back(&tokens, tmp);
		}
	}
	small_check(&tokens, 0);
	quote_check(&tokens);
	if (token_context(&tokens) == 0)
		ft_free("Syntax Error", &tokens, 0);
	expand(&tokens, env);
	return (ft_addprev(tokens));
}

void	big_check(char *s, int *size, t_lexbuf **tokens)
{
	int	i;

	i = 0;
	if (s)
	{
		while ((size_t)i < ft_strlen(s))
		{
			if (quote_break(tokens, s, &i) == 1)
				break ;
			if (token_type(s, &i) == TAB_ || token_type(s, &i) == SPACE_)
				break ;
			if ((*tokens)->type == token_type(s, &i))
				i++;
			else
				break ;
		}
	}
	if (i != 0)
		(*tokens)->value = fill_tokens(s, i, tokens);
	if (!(*tokens)->value)
		ft_free("Alloc error at big_check", tokens, 1);
	(*size) += i;
}

void	small_check(t_lexbuf **tokens, int i)
{
	t_lexbuf	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		i = 0;
		while (tmp->value && tmp->value[i])
			i++;
		if ((tmp->type == PIPE && i > 1) || (tmp->next
				&& tmp->next->type == PIPE && tmp->type == PIPE)
			|| (tmp->type == PIPE && tmp->next == NULL))
			(ft_free("parse error near '|'", tokens, 0), tmp = NULL);
		else if ((tmp->type == INREDIR && i > 2) || (tmp->next
				&& tmp->next->type == INREDIR && tmp->type == INREDIR))
			(ft_free("parse error near '<'", tokens, 0), tmp = NULL);
		else if (tmp->type == INREDIR && i == 2)
			tmp->type = HEREDOC;
		else if ((tmp->type == OUTREDIR && i > 2) || (tmp->next
				&& tmp->next->type == OUTREDIR && tmp->type == OUTREDIR))
			(ft_free("parse error near '>'", tokens, 0), tmp = NULL);
		else if (tmp->type == OUTREDIR && i == 2)
			tmp->type = APPOUTREDIR;
		if (tmp)
			tmp = tmp->next;
	}
}

int	token_type(char *s, int *i)
{
	static char	ref_tab[6] = {'<', '>', '|', ' ', '\t', 0};
	int			j;

	j = 0;
	if (s)
	{
		while (ref_tab[j])
		{
			if (s[*i] == ref_tab[j])
				return (j);
			j++;
		}
		if (!ref_tab[j])
			return (WORD);
	}
	return (-1);
}

char	*fill_tokens(char *s, int i, t_lexbuf **tokens)
{
	int		j;
	char	*value;

	j = 0;
	value = NULL;
	if (s)
	{
		value = (char *)malloc(sizeof(char) * (i + 1));
		if (!value)
		{
			ft_free("Alloc Error at fill_tokens", tokens, 1);
			return (NULL);
		}
		while (s[j] && j < i)
		{
			value[j] = s[j];
			j++;
		}
		value[j] = 0;
	}
	return (value);
}
