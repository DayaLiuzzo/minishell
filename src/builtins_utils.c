/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:10:26 by sbo               #+#    #+#             */
/*   Updated: 2024/03/26 11:01:11 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(char	*word)
{
	if (ft_strcmp(word, "echo") == 0)
		return (1);
	else if (ft_strcmp(word, "cd") == 0)
		return (2);
	else if (ft_strcmp(word, "pwd") == 0)
		return (1);
	else if (ft_strcmp(word, "export") == 0)
		return (2);
	else if (ft_strcmp(word, "unset") == 0)
		return (2);
	else if (ft_strcmp(word, "env") == 0)
		return (1);
	else if (ft_strcmp(word, "exit") == 0)
		return (2);
	return (0);
}

char	**exec_builtins(t_lexbuf *prompt, char **env)
{
	if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) == 1)
	{
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "echo") == 0)
			ft_echo(prompt);
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "pwd") == 0)
		{
			prompt->input->exit_status = 0;
			if (ft_pwd(NULL, 0) == -1)
				return (NULL);
		}
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "env") == 0)
			ft_env(prompt);
	}
	else if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) == 2)
	{
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "export") == 0)
			env = ft_export(prompt, env);
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "unset") == 0)
			env = ft_unset(prompt, env);
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "cd") == 0)
			env = ft_cd(prompt, env);
/*  		if (ft_strcmp(prompt->command, "exit") == 0)
			ft_exit(prompt); */
	}
	return (env);
}
