/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/22 15:20:06 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexbuf	*copy_tokens(t_lexbuf **tokens, t_lexbuf *current)
{
	t_lexbuf	*new;

	new = malloc(sizeof(t_lexbuf));
	if (new == NULL)
		return (NULL);
	new->type = current->type;
	new->input = current->input;
	new->next = NULL;
	new->value = ft_strdup(current->value);
	if (!new->value)
		ft_free("malloc error at new_tokens_pexpand", tokens, 1);
	return (new);
}

t_lexbuf	*remove_emptyexpands(t_lexbuf **tokens)
{
	t_lexbuf	*current;
	t_lexbuf	*new_node;
	t_lexbuf	*new_head;

	current = *tokens;
	new_node = NULL;
	new_head = NULL;
	while (current)
	{
		if (current && current->value && current->value[0] != -6)
		{
			new_node = copy_tokens(tokens, current);
			add_back(&new_head, new_node);
		}
		current = current->next;
	}
	return (ft_addprev(new_head));
}

t_lexbuf	*parsing(t_input *input, char **env)
{
	t_lexbuf	*mytokens;
	t_lexbuf	*new_tokens;
	t_lexbuf	*last_tokens;

	mytokens = token_recognition(input->linebuffer, input, 0, env);
	new_tokens = split_expands(&mytokens, input);
	quotes_removal(&new_tokens);
	pos_quotes(&new_tokens);
	last_tokens = remove_emptyexpands(&new_tokens);
	ft_free_list(&mytokens);
	ft_free_list(&new_tokens);
	return (last_tokens);
}

int	main(int ac, char **av, char **env)
{
	t_input		input;
	t_lexbuf	*tokens;

	(void)av;
	if (ac != 1)
		exit(1);
	while (1)
	{
		init_struct(&input);
		input.linebuffer = readline("minishell >");
		if (!input.linebuffer)
			break ;
		add_history(input.linebuffer);
		tokens = parsing(&input, env);
		print_stack(tokens);
		ft_free(NULL, &tokens, 0);
	}
}
