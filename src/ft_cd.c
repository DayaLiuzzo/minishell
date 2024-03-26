/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:18:26 by sbo               #+#    #+#             */
/*   Updated: 2024/03/26 15:33:18 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cd_noarg(t_lexbuf *prompt, char **env)
{
	char	*pwd;

	if (chdir("/home/sbo") == -1) // voir comment avoir user ??env 
		return (perror ("minishell : cd: "), env);
	pwd = ft_strjoin("PWD=", "/home/sbo");
	if (!pwd)
		return (NULL);
	env = ft_export_cd(env, pwd);
	if (!env)
		return (free(pwd), NULL);
	ft_pwd(NULL, -1);
	prompt->input->exit_status = 0;
	return (env);
}


char	**cd_direct_path(t_lexbuf *prompt, char **env, char *oldpwd, char *arg)
{
	int		check;
	char	*pwd;

	check = ft_chdir(arg);
	if (check == -1)
		return (perror ("minishell : cd: "), free(oldpwd),
			change_exit_status(&prompt->input->exit_status, 1), env);
	if (check == -2)
		return (free(oldpwd), NULL);
	if (ft_strcmp(arg, "..") == 0)
		pwd = trunc_path(oldpwd);
	else
		pwd = ft_strjoin2(oldpwd, "/", arg, 0);
	if (!pwd)
		return (free(oldpwd), NULL);
	pwd = ft_strjoin2("PWD=", pwd, NULL, 2);
	if (!pwd)
		return (free(oldpwd), NULL);
	env = ft_export_cd(env, pwd);
	free(oldpwd);
	prompt->input->exit_status = 0;
	return (env);
}

char	**cd_move_with_absolut_path(t_lexbuf *prompt, char **env, char *arg)
{
	char	**split;
	int		check;
	int		i;

	i = 0;
	split = ft_split(arg, '/');
	if (!split)
		return (NULL);
	while (split[i])
	{
		if (arg[0] == '/' && i == 0)
		{
			split[0] = ft_strjoin2("/", split[0], NULL, 2);
			if (!split[0])
				return (free(split), NULL);
		}
		check = ft_chdir(split[i]);
		if (check == -1)
			return (free_split(split), perror ("minishell : cd: "), change_exit_status(&prompt->input->exit_status, 1), env);
		if (check == -2)
			return (free_split(split), NULL);
		i++;
	}
	return (split);
}

char	**cd_absolut_path(t_lexbuf *prompt, char **env, char *arg, char *oldpwd)
{
	char	*pwd;
	char	**split;

	if (check_path(arg) == 0)
	{
		write(2, "minishell : cd: : No such file or directory\n", 45);
		prompt->input->exit_status = 1;
		return (free(oldpwd), env);
	}
	split = cd_move_with_absolut_path(prompt, env, arg);
	if (split == env || split == NULL)
		return (free(oldpwd), split);
	free_split(split);
	if (arg[0] == '/')
		pwd = ft_strjoin ("PWD=", arg);
	else
		pwd = ft_strjoin2 ("PWD=", oldpwd, arg, 0);
	if (!pwd)
		return (free(oldpwd), NULL);
	env = ft_export_cd(env, pwd);
	free(oldpwd);
	prompt->input->exit_status = 0;
	return (env);
}

char	**ft_cd(t_lexbuf *prompt, char **env)
{
	char	*oldpwd;
	char	*arg;

	if (number_of_args(prompt) >= 2)
	{
		write(2, "cd: too many arguments\n", 24);
		prompt->input->exit_status = 1;
		return (env);
	}
	arg = extract_in_lexbuf(prompt, WORD, 2);
	oldpwd = get_oldpwd(prompt);
	if (!oldpwd && errno != ENOENT)
		return (NULL);
	if (number_of_args(prompt) == 0)
		return (cd_noarg(prompt, env));
	else if (ft_strchr2(arg, '/') == -1)
		return (cd_direct_path(prompt, env, oldpwd, arg));
	else
		return (cd_absolut_path(prompt, env, arg, oldpwd));
}
