/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:32:32 by sbo               #+#    #+#             */
/*   Updated: 2024/03/26 15:33:27 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int manage_static(char *buffer, int ls, int *link)
{
    if (ls == -2 && buffer)
        free(buffer);
    if (ls == -1)
        *link = 0;
    if (ls == 1 && buffer)
        return (ft_strlen(buffer));
    return (0);
}

char    *add_static(char *buffer, char *str)
{
    char *tmp;

    if (ft_strcmp(str, "..") == 0)
        tmp = trunc_path(buffer);
    else
        tmp = ft_strjoin2(buffer, "/", str, 0);
    if (!tmp)
    {
        if (buffer)
            free(buffer);
        return (NULL);
    }
    if (check_path(tmp) == 0)
        return (free(tmp),buffer);
    free(buffer);
    return (tmp);
}

char    *get_current_path(char *buffer)
{
    char *tmp;

    tmp = NULL;
    tmp = getcwd(tmp, 0);
    if (!tmp && errno == ENOENT)
    {
        if (buffer) 
            return (buffer);
    }
/*     else if (!tmp)
        return (NULL); */
    if (buffer)
        free(buffer);
    return (ft_strdup(tmp));
}

int    ft_pwd(char *str, int ls)
{
    static char *buffer;
    static int  link = 0;
    int len;

    if (ls == -2 || ls == -1 || ls == 1 ||ls == 3)
        return (manage_static(buffer, ls, &link));
    else if (ls == 2)
    {
        if (link == 1)
        {
            len = ft_strlen(buffer);
            buffer = add_static(buffer, str);
            if (!buffer)
                return (-1);
            if (len == (int)ft_strlen(buffer))
                return (0);
            return (1);
         }
        else
            return (0);
    }
    if (ls == 3)
    {
        ls = 0;
        while (buffer[ls])
        {
            str[ls] = buffer[ls];
            ls++;
        }
        str[ls] = 0;
        return (0);
    }
    if (!str && link == 0)
    {
        buffer = get_current_path(buffer);
        if (!buffer && errno != ENOENT)
            return (-1);
    }   
    else if (str)
    {
        link = 1;
        if (buffer)
            free(buffer);
        buffer = ft_strdup(str);
        if (!buffer)
            return (-1);
        return (0);
    }
    printf("%s\n", buffer);
    return (0); 
}
