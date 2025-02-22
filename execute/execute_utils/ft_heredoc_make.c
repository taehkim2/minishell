/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_make.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:39:38 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/14 19:27:37 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(t_pipe *pipes, char *eof, int cnt)
{
	char	*line;

	heredoc_mode();
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			eof_in_heredoc();
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(pipes->heredoc[cnt][1], line, ft_strlen(line));
		write(pipes->heredoc[cnt][1], "\n", 1);
		free(line);
	}
	heredoc_close(pipes);
	exit(0);
}

int	heredoc_put_char(t_pipe *pipes, char *eof, int cnt)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	if (pipes->heredoc[cnt][0] != -1 && pipes->heredoc[cnt][1] != -1)
		close(pipes->heredoc[cnt][0]);
	if (pipe(pipes->heredoc[cnt]) == -1)
		error_end("pipe failed");
	pid = fork();
	if (pid < 0)
		error_end("fork failed");
	else if (pid == 0)
		heredoc_child(pipes, eof, cnt);
	else if (pid > 0)
	{
		waitpid(pid, &(pipes->status), 0);
		status_check_heredoc(&(pipes->status));
		if (pipes->status != 0)
			return (END);
	}
	close(pipes->heredoc[cnt][1]);
	return (NEXT);
}

int	heredoc_init(t_list *list, t_pipe *pipes, int cnt)
{
	while (cnt < pipes->heredoc_fl_cnt)
	{
		pipes->heredoc[cnt][0] = -1;
		pipes->heredoc[cnt][1] = -1;
		cnt++;
	}
	cnt = 0;
	while (list != NULL)
	{
		if (list->info.flgs == F_DLESS)
		{
			if (heredoc_put_char(pipes, list->next->info.token, cnt))
			{
				heredoc_close(pipes);
				return (END);
			}
		}
		else if (list->info.flgs == F_PIPE)
			cnt++;
		list = list->next;
	}
	return (NEXT);
}

int	heredoc_creat(t_list *list, t_pipe *pipes)
{
	t_list	*head;

	pipes->heredoc_cnt = 0;
	pipes->heredoc_fl_cnt = 1;
	head = list;
	while (list != NULL)
	{
		if (list->info.flgs == F_PIPE)
			pipes->heredoc_fl_cnt++;
		list = list->next;
	}
	pipes->heredoc = \
	(int (*)[2])malloc(sizeof(int [2]) * pipes->heredoc_fl_cnt);
	if (pipes->heredoc == NULL)
		error_end("malloc failed");
	if (heredoc_init(head, pipes, 0))
		return (END);
	return (NEXT);
}
