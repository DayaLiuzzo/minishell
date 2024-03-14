/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:24:06 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/14 13:08:14 by dliuzzo          ###   ########.fr       */
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

char *fill_tokens(char *s, int i, t_lexbuf **tokens, t_input *input)
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
void	big_check(char *s, int *size, t_lexbuf **tokens, t_input *input)
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
			if((*tokens)->type == token_type(s, &i))
				i++;
			else 
				break;
		}
	}
	if (i != 0)
	(*tokens)->value = fill_tokens(s, i, tokens, input);
	if(!(*tokens)->value)
		ft_free("Alloc error at big_check", input, tokens, 1);
	(*size) += i;
}


t_lexbuf	*new_tokens(char *s, int *i)
{
	t_lexbuf	*new;

	new = malloc(sizeof(t_lexbuf));
	if (new == NULL)
		return (NULL);
	new->value = NULL;
	new->type = token_type(s, i);
	new->next = NULL;
	return (new);
}

t_lexbuf *token_recognition(char *s, t_input *input, int i, char **env)
{
    t_lexbuf *tokens;
    t_lexbuf *tmp;
    
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
				ft_free("Alloc Failure in new_tokens", input, &tokens, 1);
			big_check(&s[i], &i, &tmp, input);
			if (tmp->value[0])
				add_back(&tokens, tmp);
		}
    }
	small_check(&tokens, input);
	quote_check(&tokens, input);
	if (token_context(input, &tokens) == 0 )
		ft_free("Syntax Error", input, &tokens, 0);
	expand(&tokens, input, env);
	return (ft_addprev(tokens));
}

void small_check(t_lexbuf **tokens, t_input *input)
{
	t_lexbuf *tmp;
	int i;

	tmp = *tokens;
	while (tmp)
	{
		i = 0;
		while(tmp->value && tmp->value[i])
			i++;
		if((tmp->type == PIPE && i > 1) || 
		(tmp->next && tmp->next->type == PIPE && tmp->type == PIPE))
			(ft_free("parse error near '|'", input, tokens, 0),tmp = NULL);
		else if((tmp->type == INREDIR && i > 2 ) ||
		(tmp->next && tmp->next->type == INREDIR && tmp->type == INREDIR)) 
			(ft_free("parse error near '<'", input, tokens, 0),tmp = NULL);
		else if(tmp->type == INREDIR && i == 2)
			tmp->type = HEREDOC;
		else if((tmp->type == OUTREDIR && i > 2 )||
		(tmp->next && tmp->next->type == OUTREDIR && tmp->type == OUTREDIR)) 
			(ft_free("parse error near '>'", input, tokens, 0),tmp = NULL);
		else if(tmp->type == OUTREDIR && i == 2)
			tmp->type = APPOUTREDIR;
		if(tmp)
			tmp = tmp->next;
	}
}

void	quote_check(t_lexbuf **tokens, t_input *input)
{
	t_lexbuf *tmp;
	int i;
	int inquote;

	i = 0;
	inquote = 2;
	tmp = *tokens;
	tmp = get_last(tmp);
	while(tmp && tmp->value[i])
	{
		
		if(tmp->value[i] == '"')
		{
			inquote++;
			skip(tmp->value, &i, '"');
			if(tmp->value[i] == '"')
			inquote++;
		}
		if(tmp->value[i] == '\'')
		{
			inquote++;
			skip(tmp->value, &i, '\'');
			if(tmp->value[i] == '\'')
			inquote++;
		}
		i++;
	}
	if(inquote % 2 == 0)
		return;
	ft_free("Quotes fucked up", input, tokens, 0);
}

int	token_context(t_input *input, t_lexbuf **tokens)
{
	t_lexbuf *tmp;
	
	tmp = *tokens;
	
	while(tmp)
	{
		if (tmp->type == INREDIR)
		{
			if(precise_token(input, &tmp, tokens, INREDIR)== 0)
				return(0);
		} 
		else if (tmp->type == OUTREDIR)
		{
			if(precise_token(input, &tmp, tokens, OUTREDIR)== 0)
				return(0);
		}
		else if (tmp->type == HEREDOC)
		{
			if(precise_token(input, &tmp, tokens, HEREDOC)== 0)
				return(0);
		}
		else if (tmp ->type == APPOUTREDIR)
		{
			if(precise_token(input, &tmp, tokens, APPOUTREDIR)== 0)
				return(0);
		}
		if(tmp)
			tmp = tmp->next;
	}
	return(1);
}

int	precise_token(t_input *input, t_lexbuf **tmp, t_lexbuf **tokens, int type)
{
	t_lexbuf *current;
	
	current = *tmp;
	if(tmp)
	{
		if(!(*tmp)->next)
			return (0);
		else if((*tmp)->next->type != WORD)
			return (0);
		else
		{
			(*tmp)->type = type;
			free((*tmp)->value);
			(*tmp)->value = NULL;
			(*tmp)->value = ft_strdup((*tmp)->next->value);
			if(!(*tmp)->value)
				ft_free("Alloc Error at ft_inredir", input, tokens, 1);
			current = current->next;
			(*tmp)->next = (*tmp)->next->next;
			free(current->value);
			free(current);
			return (1);
		}		
	}
	return (0);
}

