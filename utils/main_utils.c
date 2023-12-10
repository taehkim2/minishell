/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:25:40 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/11 01:27:23 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_envp(char **envp)
{
	int	idx;

	idx = 0;
	while (envp[idx] != NULL)
	{
		envp[idx] = ft_strdup(envp[idx]);
		idx++;
	}
}

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

char	*line_creat(void)
{
	char	*line;
	char	*tmp;

	line = readline("minishell$ ");
	if (line == NULL)
		exit(0);
		// error_end("readline failed");
	if (line[0] == '\0')
		return (line);
	while (1)
	{
		if (line_check(line))
			break ;
		tmp = readline("> ");
		if (tmp == NULL)
			exit(0);
			// error_end("readline failed");
		line = my_strjoin(&line, tmp);
		if (line == NULL)
			error_end("malloc failed");
		free(tmp);
	}
	return (line);
}
