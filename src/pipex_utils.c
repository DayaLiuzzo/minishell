/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:54:48 by sbo               #+#    #+#             */
/*   Updated: 2024/03/26 10:56:34 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_arg(t_lexbuf *tmp, char **env, int *len)
{
	if (*len == 0)
		return (check_cmd(env, tmp->value));
	else
		return (tmp->value);
}

char	**ft_join_word(t_lexbuf *prompt, char **env)
{
	t_lexbuf	*tmp;
	char		**join_word;
	int			len;

	len = get_len_cmd(prompt);
	tmp = prompt;
	join_word = malloc((len + 1) * sizeof(char *));
	if (!join_word)
		return (NULL);
	len = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			join_word[len] = fill_arg(tmp, env, &len);
			if (!join_word[len] && len == 0)
				return (free(join_word), NULL);
			len++;
		}
		tmp = tmp->next;
	}
	join_word[len] = NULL;
	return (join_word);
}

void	free_child(t_lexbuf *prompt)
{
	while (prompt->prev)
		prompt = prompt->prev;
	ft_pwd(NULL, -2);
	free (prompt->input->linebuffer);
	free_env(prompt->env);
	ft_free_list(&prompt);
}

int	get_output(t_lexbuf *prompt, int *tube)
{
	int	fd2;
	int	output;

	output = get_out(prompt);
	if (output == -1)
	{
		free_child(prompt);
		exit(1);
	}
	if (output != -2)
	{
		fd2 = output;
		dup2(fd2, 1);
		close(fd2);
	}
	else if (output == -2 && is_last_cmd(prompt) == 0)
		dup2(tube[1], 1);
	close(tube[1]);
	return (0);
}

void	job(t_lexbuf *prompt, int *tube, char **env)
{
	char	**split;

	get_output(prompt, tube);
	if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) != 0)
	{	
		if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) != 2
			|| have_pipe(prompt) == 1)
			prompt->env = exec_builtins(prompt, env);
		free_child(prompt);
		if (prompt->input->exit_status != 0)
			exit (prompt->input->exit_status);
		exit (EXIT_SUCCESS);
	}
	split = ft_join_word(prompt, env);
	if (!split)
	{
		free_child(prompt);
		exit(127);
	}
	execve(split[0], split, env);
	free_split(split);
	exit(1);
}
