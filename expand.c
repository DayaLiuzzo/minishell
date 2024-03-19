/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:58:02 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/19 16:32:04 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_lexbuf **tokens, char **env)
{
	t_lexbuf	*tmp;
	t_utils		utils;
	char		*envar;
	char		*new_value;

	init_utils(&utils);
	tmp = (*tokens);
	negate_quotes(tokens);
	while (tmp)
	{
		while (tmp->value && tmp->type != HEREDOC
			&& (utils.start = find_envar(tmp->value, 0)) != -1)
		{
			init_utils(&utils);
			envar = get_envar(tmp->value, env, tokens, &utils);
			new_value = concatene_envar(tmp->value, envar, tokens, &utils);
			if (tmp->value)
				free(tmp->value);
			tmp->value = new_value;
		}
		tmp = tmp->next;
	}
}

char	*get_envar(char *value, char **env, t_lexbuf **tokens, t_utils *utils)
{
	int		i;
	int		j;
	char	*varname;
	char	*varcontent;

	i = 0;
	j = 0;
	varcontent = NULL;
	varname = get_varname(value, tokens, utils);
	if (!varname)
		return (NULL);
	while (env[i])
	{
		if (strncmp_env(varname, env[i], utils->varname_len) == 1)
		{
			while (env[i][j] && env[i][j] != '=')
				j++;
			utils->varcontent_start = j + 1;
			if ((varcontent = get_varcontent(env[i], tokens, utils,
						value)) == NULL)
				return (NULL);
			if (varname)
				free(varname);
			return (varcontent);
		}
		i++;
	}
	return (varcontent);
}

char	*expand_left(char *value, char *envar, t_lexbuf **tokens,
		t_utils *utils)
{
	int		i;
	int		k;
	char	*tmp;

	k = 0;
	utils->start += -1;
	i = utils->start;
	tmp = NULL;
	while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
		i++;
	if ((tmp = (char *)malloc(sizeof(char) * (utils->start
					+ utils->varcontent_len + 1))) == NULL)
		ft_free("Alloc error concatene_envar", tokens, 1);
	i = 0;
	while (i < utils->start)
	{
		tmp[i] = value[i];
		i++;
	}
	while (i < utils->start + utils->varcontent_len && envar[k])
	{
		tmp[i] = envar[k];
		i++;
		k++;
	}
	tmp[i] = 0;
	return (tmp);
}

char	*concatene_envar(char *tokenvalue, char *envar, t_lexbuf **tokens,
		t_utils *utils)
{
	char	*tmp;
	char	*new_value;
	int		i;
	char	*tmp2;

	tmp = NULL;
	new_value = NULL;
	i = find_envar(tokenvalue, 0);
	tmp = expand_left(tokenvalue, envar, tokens, utils);
	while (tokenvalue[i] && (ft_isalnum(tokenvalue[i]) || tokenvalue[i] == '_'))
		i++;
	tmp2 = &tokenvalue[i];
	new_value = ft_strjoin(tmp, tmp2);
	if (tmp)
		free(tmp);
	return (new_value);
}
