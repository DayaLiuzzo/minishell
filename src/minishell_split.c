/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:27:50 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/04 20:53:30 by dliuzzo          ###   ########.fr       */
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
    else if(s[split->i] && s[split->i]== '"')
    {
        split->i++;
        while(s[split->i] && s[split->i] != '"')
            split->i++;
    }
}

void ft_double_loop(t_split *split, char *s)
{
    //   printf("\n\ndquote->%d     squote->%d index--->%i\n\n\n", split->dquote, split->squote, split->i);
    split->dquote +=1;
    if(split->dquote % 2 == 0)
    {
        
        split->i++;
        // printf("char current --->%c\n", s[split->i]);
    }
    else
    {
        split->i++;
        while(s[split->i] && s[split->i] != '"')
        {    
            split->i++;     
            // printf("char current --->%c\n", s[split->i]);
        }
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
// ""ls -l""
void ft_count_words(t_split *split, char *s)
{
    split->word_count = 0;
    while(s[split->i])
    {
        while(s[split->i] && (is_space(s[split->i]) == 1))
            split->i++;
        if(s[split->i] && (is_space(s[split->i]) == 0)) 
        {
            // printf("dquote->%d     squote->%d index--->%i\n", split->dquote, split->squote, split->i);
            if((split->dquote == 0 && split->squote ==  0 ) || 
            ((split->dquote != 0 && split->dquote % 2 == 0)
            || (split->squote != 0 && split->squote % 2 == 0)))
            {
                split->word_count++;
                printf("single quote--->%i\n", split->squote);
                printf("double quote--->%i\n", split->dquote);
                printf("words ----> %i\nInderx-----> %i\n\n\n", split->word_count, split->i);
            }
            while(s[split->i] && (is_space(s[split->i]) == 0))
            {
                if(s[split->i] && s[split->i]== 39)
                    ft_single_loop(split, s);
                else if(s[split->i] && s[split->i]== '"')
                    ft_double_loop(split, s);
                else if(s[split->i] && is_space(s[split->i]) == 0)
                    split->i++;
            } 
        }
                // printf("Fwords ----> %i\nFInderx-----> %i\n\n\n", split->word_count, split->i);
    }
    
}

void minishell_split(char *s)
{
    t_split split;
    if(!s)
        exit(0);
    split.squote = 0;
    split.dquote = 0;
    ft_count_words(&split, s);
    
}