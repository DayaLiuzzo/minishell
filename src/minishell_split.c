/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:27:50 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/04 17:25:13 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_space(char c)
{
    if(c == ' ' || c == 9)
        return 1;
    return 0;
}

void ft_skip(t_split *split, char *s)
{
    if(s[split->i] && (is_space(s[split->i]) == 1))
        while(s[split->i] && is_space(s[split->i]))
            split->i++;
    else if(s[split->i] && s[split->i]== 39)
    {
        split->i++;
        while(s[split->i] && s[split->i] != 39)
            split->i++;
    }
    else if(s[split->i] && s[split->i]== '"')
    {
        split->i++;
        while(s[split->i] && s[split->i] != '"')
            split->i++;
    }
}
// ""ls -l""
void ft_count_words(t_split *split, char *s)
{
    split->word_count = 0;
    while(s[split->i])
    {
        while(s[split->i] && (is_space(s[split->i]) == 1))
            ft_skip(split, s);
        
        if(s[split->i] && (is_space(s[split->i]) == 0)) 
        {
            split->word_count++;
            while(s[split->i] && (is_space(s[split->i]) == 0))
            {
                if(s[split->i] && s[split->i]== 39)
                    ft_skip(split, s);
                else if(s[split->i] && s[split->i]== '"')
                    ft_skip(split, s);
                else
                    split->i++;
            } 
        }
    }
}

void minishell_split(char *s)
{
    t_split split;
    if(!s)
        exit(0);
    ft_count_words(&split, s);
    printf("fin i---->%i\nwords----->%i\n", split.i, split.word_count);
}