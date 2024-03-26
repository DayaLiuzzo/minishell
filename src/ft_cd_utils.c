/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:15:11 by sbo               #+#    #+#             */
/*   Updated: 2024/03/25 19:04:02 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr2(char *s, int c)
{
	int	cpt;

	if (s == NULL)
		return (-1);
	cpt = 0;
	c = (unsigned char)c;
	while (s[cpt])
	{
		if (s[cpt] == c)
			return (1);
		cpt++;
	}
	return (-1);
}

char	*get_actual_path(char *path)
{
	char	*chaine;

	chaine = NULL;
	chaine = getcwd(chaine, 0);
	if (!chaine)
		return (NULL);
	chaine = ft_strjoin2(chaine, "/", path, 1);
	if (!chaine)
		return (NULL);
	return (chaine);
}

int	check_link(char *chaine, char *path)
{
	struct stat	sb;

	if (chdir(path) == -1)
		return (-1);
	lstat(chaine, &sb);
	if ((sb.st_mode & 0xf000) == 0xa000)
	{
		if (ft_pwd(chaine, 0) == -1)
			return (free(chaine), -2);
	}
	else
		ft_pwd(NULL, -1);
	free(chaine);
	return (0);
}

int	go_to_first_rep(char *path)
{
	if (chdir(path) == -1)
		return (-1);
	ft_pwd(NULL, -1);
	return (0);
}

int	ft_chdir(char *path)
{
	char		*chaine;
	int			tmp;

	if (path[0] == '/')
		return (go_to_first_rep(path));
	tmp = ft_pwd(path, 2);
	if (tmp == 1)
	{
		chaine = malloc(ft_pwd(NULL, 1) + 1);
		if (!chaine)
			return (-2);
		ft_pwd(chaine, 3);
		if (chdir(path) == -1)
			return (-1);
		return (free(chaine), 0);
	}
	else if (tmp == -1)
		return (-2);
	else
	{
		chaine = get_actual_path(path);
		if (!chaine)
			return (-2);
	}
	return (check_link(chaine, path));
}
