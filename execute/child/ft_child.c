/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:54:15 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/08 17:37:58 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_pipe *pipes)
{
	// next에 쓰기
	close(pipes->next_fd[0]);
	dup2(pipes->next_fd[1], STDOUT_FILENO);
	close(pipes->next_fd[1]);
}

void	mid_child(t_pipe *pipes)
{
	// prev 읽기
	close(pipes->prev_fd[1]);
	dup2(pipes->prev_fd[0], STDIN_FILENO);
	close(pipes->prev_fd[0]);
	// next에 쓰기
	close(pipes->next_fd[0]);
	dup2(pipes->next_fd[1], STDOUT_FILENO);
	close(pipes->next_fd[1]);
}

void	last_child(t_pipe *pipes)
{
	// prev 읽기
	close(pipes->prev_fd[1]);
	dup2(pipes->prev_fd[0], STDIN_FILENO);
	close(pipes->prev_fd[0]);
	close(pipes->next_fd[0]);
	close(pipes->next_fd[1]);
}

void	pipe_setting_for_child(t_pipe *pipes, int last)
{
	if (pipes->prev_fd[0] == -1 && pipes->prev_fd[1] == -1)
		first_child(pipes);
	else if (last)
		last_child(pipes);
	else
		mid_child(pipes);
}

int	child(t_list *list, t_pipe *pipes, char **envp)
{
	char	**args;
	int		last_flag;

	last_flag = is_it_last_order(list);
	pipe_setting_for_child(pipes, last_flag);
	redirection_handling(list, pipes);
	args = args_make(list);
	if (builtin(args, envp) == 0)
		simple_command(args, envp);
	args_free(&args);
	exit(0);
}
