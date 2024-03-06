/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:23:11 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/05 18:25:17 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_error_env(char *msg, t_args *myenv)
{
    if (msg)
        printf("%s\n", msg);
    if (myenv)
        ft_free_env(myenv);
    exit(0);
}
void ft_free_env(t_args *myenv)
{
	t_args	*tmp;

	if (myenv)
	{
		tmp = myenv;
		while (myenv)
		{
			tmp = myenv;
			myenv = tmp->next;
			if (tmp->varname)
				free(tmp->varname);
			free(tmp);
		}
	}
}

t_args *ft_next_env_var(t_args *args,char *value)
{
	t_args *new;
    
    
	new = (t_args *)malloc(sizeof(t_args));
	if (!new)
        ft_error_env("ALLOC ERROR", args);
	new->varname = ft_strdup(value);
    if(!new->varname)
        ft_error_env("ALLOC ERROR", args);
    new->next = NULL;
    
	return (new);
}

t_args *get_args(char **test)
{
    int i;
    t_args *ea;
	t_args *myenv;
    
    ea = NULL;
	myenv = NULL;
    i = 0;
    while (env[i] != NULL)
		i++;
	i = i - 1;
	while (i >= 0)
	{
		ea = ft_next_env_var(myenv, env[i]);
		ea->next = myenv;
		myenv = ea;
		i--;
	}
	return (myenv);
}