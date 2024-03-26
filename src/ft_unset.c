/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:26:21 by sbo               #+#    #+#             */
/*   Updated: 2024/03/26 11:00:22 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_newenv(char **varname, char **env)
{
	int	i;
	int	j;
	int	m;

	i = 0;
	m = 0;
	while (env[i])
	{
		j = 0;
		while (varname[j])
		{
			if (strcmp_equal(env[i], varname[j]) == 0
				&& is_only(varname, j) == 1)
				m++;
			j++;
		}
		i++;
	}
	return (i - m);
}

int	creat_new_env_unset(char **env, char **args, char **new_env)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (env[i])
	{
		j = 1;
		while (j >= 0 && args[j])
		{
			if (strcmp_equal(env[i], args[j]) == 0 && is_only(args, j) == 1)
				j = -2;
			j++;
		}
		if (j >= 0)
		{
			new_env[k] = ft_strdup(env[i]);
			if (!new_env[k])
				return (free_split(args), free_env(env), -1);
			k++;
		}
		i++;
	}
	new_env[k] = NULL;
	return (0);
}

char	**ft_unset(t_lexbuf *prompt, char **env)
{
	char	**new_env;
	char	**args;
	int		len;

	if (number_of_args(prompt) == 0)
		return (env);
	args = ft_join_word2(prompt);
	if (!args)
		return (NULL);
	len = get_len_newenv(args, env);
	new_env = malloc((len + 1) * sizeof(char *));
	if (!new_env)
		return (free_split(args), NULL);
	if (creat_new_env_unset(env, args, new_env) == -1)
		return (NULL);
	free_env(env);
	free(args);
	prompt->input->exit_status = 0;
	return (new_env);
}
