/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:34:31 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/11 16:44:56 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_varname(char *value, t_input *input, t_lexbuf **tokens)
{
    int i;
    int j;
    char *tmp;
    
    i = 0;
    j = 0;
    tmp = NULL;
    while(value[i] && (is_alnum(value[i]) || value[i] == '_'))
        i++;
    tmp = (char *)malloc(sizeof(char) * (i + 1));
    if (!tmp)
        ft_free("Alloc Error at get_envar", input, tokens, 1);
    while(j != i)
    {
        tmp[j] = value[j];
        j++;
    }
    tmp[j] = 0;
    return tmp;
}

char *get_varcontent(char *value, t_input *input, t_lexbuf **tokens)
{
    int i;
    int j;
    char *tmp;
    
    i = 0;
    j = 0;
    tmp = NULL;
    while(value[i])
        i++;
    tmp = (char *)malloc(sizeof(char) * (i + 1));
    if (!tmp)
        ft_free("Alloc Error at get_envar", input, tokens, 1);
    while(j != i)
    {
        tmp[j] = value[j];
        j++;
    }
    tmp[j] = 0;
    return tmp;
}
int	ft_strncmpp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (s1 || s2)
	{
		while (s1 && s1[i] && s2 && s2[i] && i < n)
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
int		find_envar(char *arg);
{
    int i;

	i = 0;
    if(arg)
    {
	    while (arg[i] && arg[i] != '$')
	    {
		    if (arg[i] == '$')
			    if (arg[i + 1])
				    if (is_alpha(arg[i + 1] == 1 || arg[i + 1]) == '_' || arg[i
					    + 1] == '$')
					    return (i++;);
            i++;
	    }
    }
    return (-1)
}
