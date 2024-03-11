/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:52 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/11 18:54:03 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexbuf	*ft_addprev(t_lexbuf *token)
{
	t_lexbuf	*tmp;
	t_lexbuf	*tmp2;

	if (token)
	{
		token->prev = NULL;
		tmp = token;
		tmp2 = token->next;
		while (tmp && tmp2)
		{
			tmp2->prev = tmp;
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
	}
	return (token);
}