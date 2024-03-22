/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/22 16:09:51 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
