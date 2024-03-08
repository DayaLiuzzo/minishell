/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:55:20 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/08 12:57:24 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_stack(t_lexbuf *tokens)
{
    int i = 0;
    t_lexbuf *tmp;
    tmp = tokens;
    while(tmp)
    {
        printf("top node Nb %i ----> value : %s\n", i, tmp->value);
        if(tmp->next == NULL)
            break;
        tmp = tmp->next;
        i++;
    }
    i = 0;
    while(tmp)
    {
        printf("prev node Nb %i ----> value : %s\n", i, tmp->value);
        tmp = tmp->prev;
        i++;
    }
}

int is_space(char c)
{
    if(c == ' ' || c == 9)
        return 1;
    return 0;
}

void print_tab(char **strs)
{
    if(strs)
    {
    int i = 0;
    while(strs[i])
    {
        printf("str%i : %s.\n",i, strs[i]);
        i++;
    }
    }
}