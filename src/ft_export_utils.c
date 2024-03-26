/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:29:17 by sbo               #+#    #+#             */
/*   Updated: 2024/03/25 19:09:29 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_is_in_env(char *var_env, char **args, int *tab_nbr)
{
	int	j;

	j = 1;
	while (args[j])
	{
		if (strcmp_equal(args[j], var_env) == 0 && tab_nbr[j] == 2)
			return (j);
		j++;
	}
	return (0);
}

int	ft_strcmp2(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '=' && str2[i] != '=')
	{
		if (str1[i] < str2[i])
			return (1);
		else if (str1[i] > str2[i])
			return (0);
		i++;
	}
	if (str1[i] == '=' && str2[i] != '=')
		return (1);
	return (0);
}

int	nbr_inf(char **env, char *arg)
{
	int	i;
	int	inf;

	inf = 0;
	i = 0;
	while (env[i])
	{
		if (ft_strcmp2(env[i], arg) == 1)
			inf++;
		i++;
	}
	return (inf);
}
