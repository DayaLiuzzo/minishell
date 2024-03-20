/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:58:02 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/20 13:51:14 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char 	*mark_empty_expand(t_lexbuf **tokens)
{
	char *str;
	
	str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		ft_free("ALLOCATION ERROR AT mark_empty_expand", tokens, 1); 
	
	str[0] = -6;
	str[1] = '\0';
	return (str); 
}
void	do_expansion(t_lexbuf *tmp, t_lexbuf **tokens, char **env,
		t_utils *utils)
{
	char	*envar;
	char	*new_value;

	init_utils(utils);
	envar = get_envar(tmp->value, env, tokens, utils);
	printf("envar --> %s\n", envar);
	new_value = concatene_envar(tmp->value, envar, tokens, utils);
	if (tmp->value)
		free(tmp->value);
	if(new_value && new_value[0] == '\0')
	{
		free(new_value);
		new_value = mark_empty_expand(tokens);
	}
	tmp->value = new_value;
}

void	expand(t_lexbuf **tokens, char **env)
{
	t_lexbuf	*tmp;
	t_utils		utils;

	init_utils(&utils);
	tmp = (*tokens);
	negate_quotes(tokens);
	while (tmp)
	{
		while (tmp->value && tmp->type != HEREDOC)
		{
			utils.start = find_envar(tmp->value, 0);
			if (utils.start != -1)
				do_expansion(tmp, tokens, env, &utils);
			else
				break ;
		}
		tmp = tmp->next;
	}
}

char	*get_envar(char *value, char **env, t_lexbuf **tokens, t_utils *utils)
{
	char	*varname;
	char	*varcontent;

	varcontent = NULL;
	varname = get_varname(value, tokens, utils, 0);
	if (!varname)
		return (NULL);
	while (env[utils->i])
	{
		if (strncmp_env(varname, env[utils->i], utils->varname_len) == 1)
		{
			while (env[utils->i][utils->j] && env[utils->i][utils->j] != '=')
				utils->j++;
			utils->varcontent_start = utils->j + 1;
			varcontent = get_varcontent(env[utils->i], tokens, utils, value);
			if (varcontent == NULL)
				return (NULL);
			if (varname)
				free(varname);
			return (varcontent);
		}
		utils->i++;
	}
	return (varcontent);
}

char	*expand_left(char *value, char *envar, t_lexbuf **tokens,
		t_utils *utils)
{
	char	*tmp;

	reset_iterators(utils);
	tmp = NULL;
	while (value[utils->i] && (ft_isalnum(value[utils->i])
			|| value[utils->i] == '_'))
		utils->i++;
	tmp = (char *)malloc(sizeof(char) * (utils->start + utils->varcontent_len
				+ 1));
	if (tmp == NULL)
		ft_free("Alloc error concatene_envar", tokens, 1);
	utils->i = 0;
	while (utils->i < utils->start)
	{
		tmp[utils->i] = value[utils->i];
		utils->i++;
	}
	while (utils->i < utils->start + utils->varcontent_len && envar[utils->j])
	{
		tmp[utils->i] = envar[utils->j];
		utils->i++;
		utils->j++;
	}
	tmp[utils->i] = 0;
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
	if(tokenvalue[i] && tokenvalue[i] == '?')
		i++;
	else 
		while (tokenvalue[i] && (ft_isalnum(tokenvalue[i]) || tokenvalue[i] == '_'))
			i++;
	tmp2 = &tokenvalue[i];
	new_value = ft_strjoin(tmp, tmp2);
	if (tmp)
		free(tmp);
	return (new_value);
}
