/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:55:20 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/01 18:19:54 by dliuzzo          ###   ########.fr       */
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
        
        printf("node Nb %i ----> value : %s\n", i, tmp->value);
        tmp = tmp->next;
        i++;
    }
}