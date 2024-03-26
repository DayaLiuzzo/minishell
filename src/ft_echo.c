/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:44:27 by sbo               #+#    #+#             */
/*   Updated: 2024/03/26 14:40:05 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)

{
	int	cpt;

	cpt = 0;
	while ((s1[cpt] == s2[cpt]) && s1[cpt] && s2[cpt])
	{
		cpt++;
	}
	if ((unsigned char)s1[cpt] > (unsigned char)s2[cpt])
		return (1);
	else if ((unsigned char)s1[cpt] < (unsigned char)s2[cpt])
		return (-1);
	else
		return (0);
}

void	ft_echo(t_lexbuf *prompt)
{
	int		i;
	char	**args;

	i = 1;
	if (!extract_in_lexbuf(prompt, WORD, 2))
	{
		printf ("\n");
		prompt->input->exit_status = 0;
		return ;
	}
	args = ft_join_word2(prompt);
	if (!args)
		exit(1); // free_tout 
	while (args[i])
	{
		if (ft_strcmp("-n", args[1]) == 0 && !args[i + 1])
			printf("%s", args[i]);
		else if (ft_strcmp("-n", args[1]) != 0 && !args[i + 1])
			printf("%s\n", args[i]);
		if ((ft_strcmp("-n", args[i]) != 0 || i != 1) && args[i + 1])
			printf("%s ", args[i]);
		i++;
	}
	free(args);
	prompt->input->exit_status = 0;
}
