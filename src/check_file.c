/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:31:07 by sbo               #+#    #+#             */
/*   Updated: 2024/03/26 11:37:14 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_in(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;
	int			fd;
	char		*in;

	fd = -2;
	tmp = prompt;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INREDIR)
		{
			fd = -1;
			in = tmp->value;
		}
		else if (tmp->type == HEREDOC)
			fd = atoi(tmp->value); //ft_atoi
		tmp = tmp->next;
	}
	if (fd == -1)
		fd = open(in, O_RDONLY);
	return (fd);
}

int	get_out(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;
	int			fd;
	char		*out;

	tmp = prompt;
	fd = -2;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUTREDIR)
		{
			fd = -4;
			out = tmp->value;
		}
		else if (tmp->type == APPOUTREDIR)
		{
			fd = -3;
			out = tmp->value;
		}
		tmp = tmp->next;
	}
	if (fd == -4)
		fd = open(out, O_WRONLY | O_TRUNC);
	else if (fd == -3)
		fd = open(out, O_WRONLY | O_APPEND);
	return (fd);
}

int	check_outfile(t_lexbuf *tmp)
{
	int	fd;

	fd = 0;
	if (tmp->type == OUTREDIR && access(tmp->value, F_OK) == 0)
		fd = open(tmp->value, O_WRONLY | O_TRUNC);
	else if (tmp->type == APPOUTREDIR && access(tmp->value, F_OK) == 0)
		fd = open(tmp->value, O_WRONLY | O_APPEND);
	else
		fd = open(tmp->value, O_CREAT, 0644);
	if (fd == -1)
	{
		tmp->input->exit_status = 1;
		return (0);
	}
	close (fd);
	return (1);
}

int	check_file(t_lexbuf *tokens)
{
	t_lexbuf	*tmp;
	int			fd;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUTREDIR || tmp->type == APPOUTREDIR)
		{
			if (check_outfile(tmp) == 0)
				return (0);
		}
		else if (tmp->type == INREDIR)
		{
			fd = open(tmp->value, O_RDONLY);
			if (fd == -1)
			{
				tmp->input->exit_status = 1;
				return (0);
			}
			close (fd);
		}
		tmp = tmp->next;
	}
	return (1);
}
