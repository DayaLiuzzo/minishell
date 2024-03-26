/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:11:38 by sbo               #+#    #+#             */
/*   Updated: 2024/03/25 19:13:03 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	ft_here_doc(char *limiter, int *tube)
{
	char	*chaine;
	char	*temp;

	temp = ft_strjoin(limiter, "\n");
	if (!temp)
		exit(1);
	while (1)
	{
		chaine = get_next_line(0);
		if (!chaine)
		{
			write (2, "here-document delimited by EOF wanted ", 38);
			write (2, temp, ft_strlen(temp));
		}
		if (!chaine || ft_strcmp(chaine, temp) == 0)
		{
			free(chaine);
			break ;
		}
		write(tube[1], chaine, ft_strlen(chaine));
		free(chaine);
	}
	close(tube[1]);
	free(temp);
}

int	is_last_in(t_lexbuf	*prompt)
{
	t_lexbuf	*tmp;

	tmp = prompt->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INREDIR || tmp->type == APPOUTREDIR)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	add_here_doc(t_lexbuf *tmp, int *tube)
{
	free(tmp->value);
	tmp->value = ft_itoa(tube[0]);
	if (!tmp->value)
		return (0);
	return (1);
}

void	open_here_doc(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;
	int			i;
	int			tube[1024][2];

	i = 0;
	tmp = prompt;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (pipe(tube[i]))
				return (perror("pipe"), exit(1));
			ft_here_doc(tmp->value, tube[i]);
			if (is_last_in(tmp) == 1)
				add_here_doc(tmp, tube[i]);
			else
				close(tube[i][0]);
			i++;
		}
		tmp = tmp->next;
	}
}