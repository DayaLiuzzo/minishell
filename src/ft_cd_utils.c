/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:15:11 by sbo               #+#    #+#             */
/*   Updated: 2024/03/27 12:25:37 by sbo              ###   ########.fr       */
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
