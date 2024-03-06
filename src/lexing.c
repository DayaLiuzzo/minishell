/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:52 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/06 16:59:11 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexbuf    *build_tokens(t_input *input, char **test)
{
    int i;
    t_lexbuf *ea;
	t_lexbuf *token;
    
    ea = NULL;
	token = NULL;
    i = 0;
	if(test)
	{
    while (test[i] != NULL)
		i++;
	i = i - 1;
	while (i >= 0)
	{
		ea = ft_nexttoken(token, input, test[i]);
		ea->next = token;
		token = ea;
		i--;
	}
	}
	return (ft_addprev(token));
}
t_lexbuf *ft_addprev(t_lexbuf *token)
{
	t_lexbuf *tmp;
	t_lexbuf *tmp2;
	
	if(token)
	{
		token->prev = NULL;
		tmp = token;
		tmp2 = token->next;
		while(tmp && tmp2)
		{
			tmp2->prev = tmp; 
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
	}
	return(token);
}
t_lexbuf *ft_nexttoken(t_lexbuf *tokens, t_input *input, char *value)
{
	t_lexbuf *new;
    
    
	new = (t_lexbuf *)malloc(sizeof(t_lexbuf));
	if (!new)
		ft_free(input, tokens, 1);
    init_tokens(new);
	new->value = ft_strdup(value);
    if(new->value == NULL)
        ft_free(input, tokens, 1);
    new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_command_table	*create_command_table(t_lexbuf *tokens)
{
	t_lexbuf *head;
	t_lexbuf *tmp;
	t_command_table *commands;

	head = tokens;
	tmp = tokens;
	commands = NULL;
	while(tmp)
	{
		quote_expand(tmp, head);
		tmp = tmp->next;
	}
	return (commands);
	
}
void in_single_quote(char *value, t_split *split)
{
	split->squote +=1;
    if(split->squote % 2 != 0)
    {
        split->i++;
        while(value[split->i] && value[split->i] != 39 && value[split->i != '-'])
            split->i++;
    }
	else 
		split->wordlen -= 2 ;
}

void in_double_quote(char *value, t_split *split)
{
	split->dquote +=1;
	if(split->squote % 2 != 0)
    {
        split->i++;
        while(value[split->i] && value[split->i] != '"' && value[split->i] != '$' && value[split->i != '-'])
            split->i++;
    }
	else
		split->wordlen -= 2;
	
}

void quote_expand(t_lexbuf *tokens, t_lexbuf *head)
{
	t_split split;
	
	split.squote = 0;
	split.dquote = 0;
	init_split_count(&split);
	if(tokens)
	{
		while(tokens->value && tokens->value[split.i])
		{
			if(tokens->value[split.i] == 39)
				in_single_quote(tokens->value, &split);
			if(tokens->value[split.i] == '"')
				in_double_quote(tokens->value, &split);
			ft_checker(tokens, head, &split);
			split.i++;
		}
	}
}

void ft_checker(t_lexbuf *tokens, t_lexbuf *head, t_split *split)
{
	if(tokens->value)
	{
		if(tokens->value[split->i] && tokens->value[split->i] == '<')
			{
				printf("< Found\n");
				ft_redir(tokens, head, split);
			}
		else if(tokens->value[split->i] && tokens->value[split->i] == '>')
			{
				printf("> Found\n");
				ft_redir(tokens, head, split);
			}
		else if(tokens->value[split->i] && tokens->value[split->i] == '$')
			printf("DOLLAR\n");
		else if(tokens->value[split->i] && tokens->value[split->i] == '-')
			printf("- FOUND\n");
	}
}