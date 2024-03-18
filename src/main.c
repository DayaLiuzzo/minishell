/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/18 18:19:23 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_input		input;
	t_lexbuf	*mytokens;
	t_lexbuf	*new_tokens;

	(void)av;
	if (ac != 1)
		exit(1);
	while (1)
	{
		init_struct(&input);
		input.linebuffer = readline("minishell >");
		add_history(input.linebuffer);
		mytokens = token_recognition(input.linebuffer, &input, 0, env);
		new_tokens = split_expands(&mytokens, &input);
		quotes_removal(&new_tokens);
		pos_quotes(&new_tokens);
		print_stack(new_tokens);
		ft_free_list(&mytokens);
		ft_free("", &new_tokens, 0);
	}
}
