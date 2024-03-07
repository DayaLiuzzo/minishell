/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:55:20 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/07 14:53:33 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env(t_args *myenv)
{
    int i = 0;
    t_args *tmp;
    tmp = myenv;
    while(tmp)
    {
        
        printf("node Nb %i ----> value : %s\n", i, tmp->varname);
        tmp = tmp->next;
        i++;
    }
}

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

void ft_double_loop(t_split *split, char *s)
{
    split->dquote +=1;
    if(split->dquote % 2 == 0)
        split->i++;
    else
    {
        split->i++;
        while(s[split->i] && s[split->i] != '"')
            split->i++;     
    }
}
void ft_single_loop(t_split *split, char *s)
{
    split->squote +=1;
    if(split->squote % 2 == 0)
        split->i++;
    else
    {
        split->i++;
        while(s[split->i] && s[split->i] != 39)
            split->i++;
    }
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