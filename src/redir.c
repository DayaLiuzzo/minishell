/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:39:20 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/06 16:46:26 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_redir(t_lexbuf *tokens,t_lexbuf *head, t_split *split)
{
	int count;
	
	count = split->i;
	if(tokens->value)
	{
		if(tokens->value[split->i] && tokens->value[split->i] == '<')
			{
				while(tokens->value[split->i] && tokens->value[split->i] == '<')
					split->i++;
				if((split->i - count) == 1)
				printf("INREDIR\n");	// ft_inredir(tokens, head, split);
				else if((split->i - count) == 2)
				printf("HEREDOC\n");	// ft_heredoc(tokens, head, split);
				else 
				printf("Syntax error near unexpected token '<<'\n");	// ft_error("Syntax error near unexpected token '<<'", head);
			}
		else if(tokens->value[split->i] && tokens->value[split->i] == '>')
		printf("OUTREDIR, %s\n", head->value);
	}
}

// void	ft_inredir(t_lexbuf *tokens, t_lexbuf *head, t_split *split)
// {
	
// }

