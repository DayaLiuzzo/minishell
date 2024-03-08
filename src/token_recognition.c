/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:24:06 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/08 13:04:40 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip(char *s, int *i, char del)
{
	(*i)++;
	while(s[*i] && s[*i] != del)
		(*i)++;
}


t_lexbuf	*get_last(t_lexbuf    *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

char *fill_tokens(char *s, int i, t_lexbuf *tokens, t_input *input)
{
	int j;
	char *value;

	j = 0;
	value = NULL;
	if(s)
	{
		value = (char *)malloc(sizeof(char) * (i + 1));
		if(!value)
		{
			ft_free("Alloc Error at fill_tokens", input, tokens, 1);
			return NULL;
		}
		while(s[j] && j < i)
		{
			value[j] = s[j];
			j++;
		}
		value[j] = 0;
	}
	return(value);
}

void	add_back(t_lexbuf **lst, t_lexbuf    *new)
{
	t_lexbuf	*tmp;

	if (lst)
	{
		if (*lst)
		{
			tmp = get_last(*lst);
			tmp->next = new;
		}
		else
			*lst = new;
	}
}

int token_type(char *s, int *i)
{
	static char	ref_tab[6] = {'<', '>', '|', ' ', '\t', 0};
	int j;

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
	return(-1);
}
void	big_check(char *s, int *size, t_lexbuf *tokens, t_input *input)
{
	int i;
	
	i = 0;
	if(s)
	{
		while(s[i])
		{
			if(s[i] == '"')
				skip(s, &i, '"');
			if(s[i] == 39)
				skip(s, &i, '\'');
			if(token_type(s, &i) == TAB_ || token_type(s, &i) == SPACE_)
				break;
			if(tokens->type == token_type(s, &i))
				i++;
			else 
				break;
		}
	}
	if (i != 0)
	tokens->value = fill_tokens(s, i, tokens, input);
	if(!tokens->value)
		ft_free("Alloc error at big_check", input, tokens, 1);
	(*size) += i;
}


t_lexbuf	*new_tokens(char *s, int *i)
{
	t_lexbuf	*new;

	new = malloc(sizeof(t_lexbuf));
	if (new == NULL)
		return (NULL);
	new->type = token_type(s, i);
	new->next = NULL;
	return (new);
}

t_lexbuf *token_recognition(char *s, t_input *input)
{
    t_lexbuf *tokens;
    t_lexbuf *tmp;
    int i;
    
    i = 0;
	tokens = NULL;
	tmp = NULL;
    while(s[i])
    {
		while(s[i] && (is_space(s[i]) == 1))
            i++;
		if(s[i] && (is_space(s[i]) == 0))
		{
			tmp = new_tokens(s, &i);
			if(tmp == NULL)
				ft_free("Alloc Failure in new_tokens", input, tokens, 1);
			big_check(&s[i], &i, tmp, input);
			if (tmp->value[0])
			add_back(&tokens, tmp);
		}
    }
	return (ft_addprev(tokens));
}