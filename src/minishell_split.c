/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:27:50 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/05 14:26:23 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void ft_count_words(t_split *split, char *s)
{
    split->word_count = 0;
    while(s[split->i])
    {
        while(s[split->i] && (is_space(s[split->i]) == 1))
            split->i++;
        if(s[split->i] && (is_space(s[split->i]) == 0)) 
        {
            if((split->dquote == 0 && split->squote ==  0 ) || 
            ((split->dquote != 0 && split->dquote % 2 == 0)
            || (split->squote != 0 && split->squote % 2 == 0)))
                split->word_count++;
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
    }
}
void init_split_count(t_split *split)
{
    split->i = 0;
    split->dquote = 0;
    split->squote = 0;
    split->wordlen = 0;
}
int get_word_len(t_split *split, char *s)
{
    init_split_count(split);
    split->i = split->end;
    while(s[split->i])
    {
        while(s[split->i] && (is_space(s[split->i]) == 1))
            split->i++;
        if(s[split->i] && (is_space(s[split->i]) == 0)) 
        {
            if((split->dquote == 0 && split->squote ==  0 ) || 
            ((split->dquote != 0 && split->dquote % 2 == 0)
            || (split->squote != 0 && split->squote % 2 == 0)))
                split->start = split->i;
            while(s[split->i] && (is_space(s[split->i]) == 0))
            {
                if(s[split->i] && s[split->i]== 39)
                    ft_single_loop(split, s);
                else if(s[split->i] && s[split->i]== '"')
                    ft_double_loop(split, s);
                else if(s[split->i] && is_space(s[split->i]) == 0)
                    split->i++;
            }
            return(split->end = split->i);
        }
    }
    return (0);
}

char *ft_malloc_words(t_split *split, char *s)
{
    char *new;
    int i;
    i = 0;
    
    split->end = get_word_len(split, s);
    split->wordlen = split->end - split->start;
    new = (char *)malloc(sizeof(char) * split->wordlen + 1);
    while(s[split->start] && split->start != split->end)
    {
        new[i] = s[split->start];
        i++;
        split->start++;
    }
    new[i] = 0;
    return (new);
    
}
void minishell_split(char *s)
{
    char **strs;
    t_split split;
    int i;
    if(!s)
        exit(0);
    init_split_count(&split);
    i = 0;
    ft_count_words(&split, s);
    
    // if((split.squote + split.dquote) % 2 != 0)
    // ;
        // return(printf("QUOTE UNCLOSED\n"));
    strs = (char **)malloc(sizeof(char*) * (split.word_count + 1));
    split.end = 0;
    while(i < split.word_count)
    {
            strs[i] = ft_malloc_words(&split, s);
            i++;
    }
    strs[i] = 0;
    // return (strs);
}