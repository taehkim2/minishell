/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_creat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:44:43 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/12 21:31:25 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_check(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len == 1 && line[0] == '|')
		return (END);
	else if (line[len - 1] == '|')
	{
		len -= 2;
		while (len >= 0 && line[len] == ' ')
			len--;
		if (len == -1)
			return (END);
		else if (line[len] == '|' || line[len] == '<' || line[len] == '>')
			return (END);
		return (NEXT);
	}
	return (END);
}

void	line_creat_child(char *line, int *line_pipes)
{
	char	*tmp;

	heredoc_mode_sig();
	close(line_pipes[0]);
	while (1)
	{
		if (line_check(line))
			break ;
		tmp = readline("> ");
		if (tmp == NULL)
			error_end("syntax error: unexpected end of file\n");
		line = my_strjoin(&line, tmp);
		if (line == NULL)
			error_end("malloc failed");
		free(tmp);
	}
	write(line_pipes[1], line, ft_strlen(line));
	close(line_pipes[1]);
	exit(0);
}

char	*line_make(int *line_pipes)
{
	char	*line;
	char	tmp[11];
	int		bytes;

	line = NULL;
	ft_bzero(tmp, 10);
	close(line_pipes[1]);
	while (1)
	{
		bytes = read(line_pipes[0], tmp, 10);
		if (bytes == 0)
			break ;
		line = my_strjoin(&line, tmp);
		if (line == NULL)
			error_end("malloc failed");
		ft_bzero(tmp, 10);
	}
	close(line_pipes[0]);
	return (line);
}

char	*end_char_is_pipe(char **line)
{
	int	line_pipes[2];
	int	status;
	int	pid;

	if (pipe(line_pipes) == -1)
		error_end("pipe failed");
	signal(SIGINT, ignore_sigint);
	pid = fork();
	if (pid < 0)
		error_end("fork failed");
	else if (pid == 0)
		line_creat_child(*line, line_pipes);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(*line);
		if (status == 1)
			return (NULL);
	}
	*line = line_make(line_pipes);
	return (*line);
}

char	*line_creat(void)
{
	char	*line;

	child_wait();
	line = readline("minishell$ ");
	if (line == NULL)
		my_exit(NULL);
	else if (line[0] == '\0')
		return (line);
	line = end_char_is_pipe(&line);
	return (line);
}
