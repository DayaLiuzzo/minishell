/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:34:31 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/15 17:57:14 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varname(char *value, t_input *input, t_lexbuf **tokens,
		t_utils *utils)
{
	int		i;
	int		j;
	char	*tmp;

	i = utils->start;
	j = 0;
	tmp = NULL;
	while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
		i++;
	utils->end = i;
	utils->varname_len = (utils->end - utils->start);
	tmp = (char *)malloc(sizeof(char) * (utils->varname_len + 1));
	if (!tmp)
		ft_free("Alloc Error at get_envar", input, tokens, 1);
	i = utils->start;
	while (j != utils->varname_len)
	{
		tmp[j] = value[i];
		j++;
		i++;
	}
	tmp[j] = 0;
	return (tmp);
}
int is_indquote(char *s, t_utils *utils)
{
	int i;
	int dquote;

	dquote = 2;
	i = utils->start;
	while(i >= 0 && s[i])
	{
		if(s[i] == -34)
			dquote++;
		i--;
	}
	if(dquote %2 != 0)
		return (1);
	dquote = 2;
	i = utils->end;
	while(s[i])
	{
		if(s[i] == -34)
		dquote++;
		i++;
	}
	if(dquote %2 != 0)
		return (1);
	return(0);
}
char	*get_varcontent(char *env_value, t_input *input, t_lexbuf **tokens,
		t_utils *utils, char *s)
{
	int		i;
	int		j;
	char	*tmp;

	i = utils->varcontent_start;
	j = 0;
	tmp = NULL;
	while (env_value[i])
		i++;
	utils->varcontent_len = i - utils->varcontent_start;
	tmp = (char *)malloc(sizeof(char) * (utils->varcontent_len + 1));
	if (!tmp)
		ft_free("Alloc Error at get_envar", input, tokens, 1);
	i = utils->varcontent_start;
	while (j != utils->varcontent_len)
	{
		tmp[j] = env_value[i];
		if((is_space(env_value[i]) == 1) && (is_indquote(s, utils) == 0))
			tmp[j] = -32;
		j++;
		i++;
	}
	tmp[j] = 0;
	return (tmp);
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
int	strncmp_env(char *s1, char *s2, int n)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s2 && s2[j] != '=')
		j++;
	if (s1 || s2)
	{
		while (s1 && s1[i] && s2 && s2[i] && i < n)
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		if (i != j)
			return (0);
		return (1);
	}
	return (0);
}
int	find_envar(char *arg)
{
	int	i;
	int	dquote;

	i = 0;
	dquote = 2;
	if (arg)
	{
		while (arg[i])
		{
			if (arg[i] == -39 && dquote % 2 == 0)
				skip(arg, &i, -39);
			if (arg[i] == -34)
				dquote++;
			if (arg[i] == '$')
			{
				if (arg[i + 1])
				{
					if (ft_isalpha(arg[i + 1]) == 1 || arg[i + 1] == '_'
						|| arg[i + 1] == '$')
						return (i + 1);
				}
			}
			i++;
		}
	}
	return (-1);
}

// int	find_envar(char *arg)
// {
// 	int	i;
// 	int	dquote;

// 	i = 0;
// 	dquote = 2;
// 	if (arg)
// 	{
// 		while (arg[i])
// 		{
//             // if (arg[i] < 0)
//             //     while(arg[i] < 0 )
//             //         i++;
// 			if (arg[i] == '\'' && dquote % 2 == 0)
// 				skip(arg, &i, '\'');
// 			if (arg[i] == '"')
// 				dquote++;
// 			if (arg[i] == '$')
// 			{
// 				if (arg[i + 1])
// 				{
// 					if (ft_isalpha(arg[i + 1]) == 1 || arg[i + 1] == '_'
// 						|| arg[i + 1] == '$')
// 						return (i + 1);
// 				}
// 			}
// 			i++;
// 		}
// 	}
// 	return (-1);
// }
