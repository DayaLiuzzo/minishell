/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fonc_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:17:41 by sbo               #+#    #+#             */
/*   Updated: 2024/03/25 19:18:38 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_equal(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	strcmp_equal(char *env, char *arg)
{
	int	i;

	i = 0;
	while ((env[i] && env[i] != '=') || (arg[i] && arg[i] != '='))
	{
		if (env[i] != arg[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2, char *s3, int checkfree)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(s1, s2);
	if (!tmp1)
		return (NULL);
	if (!s3)
	{
		if (checkfree == 1)
			free(s1);
		else if (checkfree == 2)
			free(s2);
		return (tmp1);
	}
	tmp2 = ft_strjoin(tmp1, s3);
	if (!tmp2)
		return (free(tmp1), NULL);
	free(tmp1);
	if (checkfree == 1)
		free(s1);
	else if (checkfree == 2)
		free(s2);
	else if (checkfree == 3)
		free(s3);
	return (tmp2);
}