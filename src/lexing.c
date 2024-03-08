/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:52 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/08 12:32:06 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// t_command_table	*create_command_table(t_lexbuf *tokens, char **env)
// {
// 	t_lexbuf		*head;
// 	t_lexbuf		*tmp;
// 	t_command_table	*commands;
// 	t_lexbuf		*new;

// 	head = tokens;
// 	tmp = tokens;
// 	new = NULL;
// 	commands = NULL;
// 	while (tmp)
// 	{
// 		quote_expand(tmp, head, env);
// 		tmp = tmp->next;
// 	}
// 	return (commands);
// }
// void	in_single_quote(char *value, t_split *split)
// {
// 	split->squote += 1;
// 	if (split->squote % 2 != 0)
// 	{
// 		split->i++;
// 		while (value[split->i] && value[split->i] != 39
// 			&& value[split->i != '-'])
// 			split->i++;
// 	}
// 	else
// 		split->i++;
// }

// void	in_double_quote(char *value, t_split *split)
// {
// 	split->dquote += 1;
// 	if (split->squote % 2 != 0)
// 	{
// 		split->i++;
// 		while (value[split->i] && value[split->i] != '"'
// 			&& value[split->i] != '$' && value[split->i != '-'])
// 			split->i++;
// 	}
// 	else
// 		split->i++;
// }

// void	quote_expand(t_lexbuf *tokens, t_lexbuf *head, char **env)
// {
// 	t_split	split;

// 	split.squote = 0;
// 	split.dquote = 0;
// 	init_split_count(&split);
// 	if (tokens)
// 	{
// 		while (tokens->value && tokens->value[split.i])
// 		{
// 			if (tokens->value[split.i] == 39)
// 				in_single_quote(tokens->value, &split);
// 			else if (tokens->value[split.i] && tokens->value[split.i] == '"')
// 				in_double_quote(tokens->value, &split);
// 			// ft_checker(tokens, head, &split);
// 			else if (tokens->value[split.i] && tokens->value[split.i] == '$')
// 				expand(tokens, head, env, &split);
// 			else
// 				split.i++;
// 		}
// 	}
// }

// void	expand(t_lexbuf *tokens, t_lexbuf *head, char **env, t_split *split)
// {
// 	if (tokens->value)
// 		if (tokens->value[split->i] && tokens->value[split->i] == '$')
// 			if (strlen(tokens->value) >= split->i + 1 && tokens->value[split->i
// 				+ 1] && is_expandable(tokens->value[split->i + 1]) == 1)
// 			{
// 				while (tokens->value[split->i])
// 				{
// 				}
// 			}
// }

// void ft_checker(t_lexbuf *tokens, t_lexbuf *head, t_split *split, char **env)
// {
// 	if(tokens->value)
// 	{
// 		if(tokens->value[split->i] && tokens->value[split->i] == '<')
// 			{
// 				printf("< Found\n");
// 				ft_redir(tokens, head, split);
// 			}
// 		else if(tokens->value[split->i] && tokens->value[split->i] == '>')
// 			{
// 				printf("> Found\n");
// 				ft_redir(tokens, head, split);
// 			}
// 		else if(tokens->value[split->i] && tokens->value[split->i] == '$')
// 			printf("DOLLAR\n");
// 		else if(tokens->value[split->i] && tokens->value[split->i] == '-')
// 			printf("- FOUND\n");
// 	}
// }