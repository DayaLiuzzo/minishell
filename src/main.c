/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/26 17:35:56 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_input		input;
	t_lexbuf	*tokens;
	char		**my_env;

	(void)av;
	input.nread = 0;
	if (ac != 1)
		exit(1);
	my_env = cpy_env(env);
	while (1)
	{
		init_struct(&input);
		input.linebuffer = readline("minishell >");
		if (!input.linebuffer)
			break ;
		add_history(input.linebuffer);
		input.nread = ft_strlen(input.linebuffer);
		tokens = parsing(&input, my_env);
		if (tokens)
			init_env_in_lex(tokens, my_env);
		open_here_doc(tokens);
		if (number_of_args(tokens) == -1)
			check_file(tokens);
		else
			pipex(tokens, 0, 0);
		if (tokens)
			my_env = tokens->env;
		ft_free(NULL, &tokens, 0);
	}
}
