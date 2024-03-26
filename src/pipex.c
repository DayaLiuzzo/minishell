/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:44:45 by sbo               #+#    #+#             */
/*   Updated: 2024/03/26 15:39:35 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

int	have_pipe(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;

	tmp = prompt;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	get_infile(t_lexbuf *prompt, int *tube, int fd, int ind)
{
	int	input;

	input = get_in(prompt);
	if (input == -1)
		return (perror("fd"), 1);
	close(tube[0]);
	if ((input == -2 && ind == 0))
	{
	}
	else
	{
		if (input != -2)
			fd = input;
		dup2(fd, 0);
		close(fd);
	}
	return (0);
}

void	job_parent(t_lexbuf *prompt, int *tube, int *ind, int fd)
{
	if (extract_in_lexbuf(prompt, WORD, 1))
	{
		if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) == 2
			&& check_file(prompt) && have_pipe(prompt) == 0)
		{
			prompt->env = exec_builtins(prompt, prompt->env);
			if (!prompt->env)
				return ;// tout free et exit
			init_env_in_lex(prompt, prompt->env);
		}
		if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) == 2
			&& check_file(prompt) == 0 && have_pipe(prompt) == 0)
				perror("fd");
	}
	close(tube[1]);
	if (fd != 0)
		close(fd);
	*ind = *ind + 1;
	prompt = move_by_pipe (prompt);
	pipex(prompt, tube[0], *ind);
	close(tube[0]);
}

void	get_exit_status(t_lexbuf *prompt, pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (is_last_cmd(prompt) == 1 && (have_pipe(prompt) == 1 ||  is_builtins(extract_in_lexbuf(prompt, WORD, 1)) != 2))
	{
		if (WIFSIGNALED(status))
			prompt->input->exit_status = status;
		else
			prompt->input->exit_status = WEXITSTATUS(status);
	}
}

void	pipex(t_lexbuf *prompt, int fd, int ind)
{
	pid_t	pid;
	int		tube[2];

	if (prompt)
	{
		if (pipe(tube))
			return (perror("pipe"), exit(1));
		pid = fork();
		if (pid == -1)
			return (perror("fork"), exit(1));
		else if (pid == 0)
		{
			if (check_file(prompt))
			{
				if (extract_in_lexbuf(prompt, WORD, 1))
				{
					get_infile(prompt, tube, fd, ind);
					job(prompt, tube, prompt->env);
				}
				else
				{
					free_child(prompt);
					exit(prompt->input->exit_status);
				}
			}
			else if ((have_pipe(prompt) == 1 || is_builtins(extract_in_lexbuf(prompt, WORD, 1)) != 2))
			{
				perror("fd");
				free_child(prompt);
				exit(prompt->input->exit_status);
			}
		}
		else
		{
			job_parent(prompt, tube, &ind, fd);
			get_exit_status(prompt, pid);
		}
	}
}
