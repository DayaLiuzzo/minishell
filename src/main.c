/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/27 18:13:41 by dliuzzo          ###   ########.fr       */
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
	input.exit_status = 0;
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
