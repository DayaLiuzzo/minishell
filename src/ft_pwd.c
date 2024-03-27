/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:32:32 by sbo               #+#    #+#             */
/*   Updated: 2024/03/27 12:49:55 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd(void)
{
    char    *pwd;

    pwd = NULL;
    pwd = getcwd(pwd, 0);
    if (!pwd && errno == ENOENT)
    {
		write (2, "No current path\n", 17);
        return ;
    }
    else if (!pwd)
        return ;
    printf("%s\n", pwd);
    free(pwd);
}
