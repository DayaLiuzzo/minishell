/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:46:28 by sbo               #+#    #+#             */
/*   Updated: 2024/03/25 11:39:30 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_exec(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	write(2, "no such file or directory: ", 27);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (NULL);
}

void	free_split(char **r_split)
{
	int	j;

	j = 0;
	while (r_split[j])
	{
		free(r_split[j]);
		j++;
	}
	free(r_split);
}

char	**ft_get_env(char **env)
{
	int		i;
	char	**r_split;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			r_split = ft_split(&env[i][5], ':');
			if (!r_split)
				return (NULL);
			return (r_split);
		}
		i++;
	}
	return (NULL);
}

char	*ft_join_cmd(char *path, char *cmd)
{
	char	*chaine;
	char	*path_cmd;

	chaine = ft_strjoin(path, "/");
	if (!chaine)
		return (NULL);
	path_cmd = ft_strjoin(chaine, cmd);
	if (!path_cmd)
		return (free(chaine), NULL);
	free(chaine);
	return (path_cmd);
}

char	*check_cmd(char **env, char *cmd)
{
	char	*join;
	char	**path;
	int		i;

	if (ft_strcmp(cmd, "") == 0)
		return (write(2, "Permission denied\n", 18), NULL);
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
		return (ft_exec(cmd));
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_get_env(env);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		join = ft_join_cmd(path[i], cmd);
		if (!join)
			return (free_split(path), NULL);
		if (access(join, F_OK) == 0)
		{
			if (access(join, X_OK) == 0)
				return (free_split(path), join);
		}
		free(join);
		i++;
	}
	free_split(path);
	write (2, cmd, ft_strlen(cmd));
	write (2, " : Command not found\n", 21);
	return (NULL);
}
