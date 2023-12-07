/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:19:47 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/07 14:55:31 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_list *list, char **envp, int flg)
{
	t_pipe	pipe;

	if (syntax_error(list) == ERROR)
		return ;
	while (list != NULL)
	{
		if (redirection_error(list) != ERROR && \
			command_error(list->info.token, envp) != ERROR)
		{
			if (flg == F_PIPE)
				multi_process(list, &pipe, envp);
			else
				one_process(list, envp);
		}
		args_next(&list);
	}
}
