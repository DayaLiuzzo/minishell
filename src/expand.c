/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:58:02 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/11 12:47:16 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_lexbuf **tokens, t_input *input, char **env);
{
	char *tmp;
    int start;
    
	tmp = (*)tokens;
    while(tmp)
    {
        start = -1;
        if((start = find_envar(tmp->value)) != -1)
        {
            while 
        }
    }
}

int		find_envar(char *arg);
{
    int i;

	i = 0;
	while (arg[i] && arg[i] != '$')
	{
		if (arg[i] == '$')
			if (arg[i + 1])
				if (is_alpha(arg[i + 1] == 1 || arg[i + 1]) == '_' || arg[i
					+ 1] == '$')
					return (i);
        i++;
	}
    return (-1)
}
