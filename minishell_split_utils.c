/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:53:54 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/07 15:54:07 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int wordlen_char_utils(t_split *split, char *s)
{
    if (s[split->i] && is_space(s[split->i]) == 0)
    {
        if (s[split->i]&& s[split->i +1] == '|')    
        {
            split->i++;
            return(split->end = split->i);
        }
        split->i++;
    }
    return (-1);
}

int protection(t_split *split, char *s)
{
    if(((split->dquote == 0 && split->squote ==  0 ) || 
            ((split->dquote != 0 && split->dquote % 2 == 0)
            || (split->squote != 0 && split->squote % 2 == 0))) && s[split->i] != '|')
        return 1;
    else 
        return 0;
}

int word_len_utils(t_split *split, char *s)
{
    if (s[split->i] && s[split->i]== '|')
    {
        split->start = split->i;
        split->end = split->i;
        split->i++;
        return 1;
    }
    return 0;
}
int ft_count_words_util(t_split *split, char *s)
{
        if (s[split->i] && s[split->i]== '|')
        {
            split->word_count++;
            split->i++;
            return 1;
        }
        return 0;
}