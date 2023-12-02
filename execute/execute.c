/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:25:55 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/02 12:42:47 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_char(t_list *list, char ***args, int end)
{
	int	args_idx;
	int	idx;

	args_idx = 0;
	while (args_idx < end)
	{
		idx = 0;
		(*args)[args_idx] = malloc(ft_strlen(list->info.token) + 1);
		if ((*args)[args_idx] == NULL)
			error_end("malloc failed");
		while (list->info.token != NULL && list->info.token[idx] != '\0')
		{
			(*args)[args_idx][idx] = list->info.token[idx];
			idx++;
		}
		(*args)[args_idx][idx] = '\0';
		list = list->next;
		args_idx++;
	}
	(*args)[args_idx] = NULL;
}

char	**args_make(t_list **list)
{
	t_list	*list_head;
	char	**args;
	int		args_idx;

	args_idx = 0;
	list_head = *list;
	while (*list != NULL && (*list)->info.flgs != F_PIPE)
	{
		*list = (*list)->next;
		args_idx++;
	}
	if (*list != NULL)
		*list = (*list)->next;
	if (args_idx == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (args_idx + 1));
	if (args == NULL)
		error_end("malloc failed");
	put_char(list_head, &args, args_idx);
	return (args);
}

void	args_free(char ***args)
{
	int	idx;

	idx = 0;
	while ((*args)[idx] != NULL)
		free((*args)[idx++]);
	free(*args);
}

char	*builtin(char **args, char **envp, char **result)
{
	char	*command;

	command = args[0];
	if (ft_strncmp(command, "echo", 3) == 0)
		echo(args);
	else if (ft_strncmp(command, "cd", 5) == 0)
		cd(args);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		pwd(args);
	else if (ft_strncmp(command, "export", 7) == 0)
		export(args, envp);
	else if (ft_strncmp(command, "unset", 6) == 0)
		unset(args, envp);
	else if (ft_strncmp(command, "env", 4) == 0)
		env(args, envp);
	else if (ft_strncmp(command, "exit", 5) == 0)
		exit(args);
	return (NULL);
}

char	*simple_command(char **args, char **envp, char **result)
{
	(void)args;
	(void)envp;
	return (NULL);
}

void	execute(t_list *list, char **envp)
{
	char	**args;
	char	*result;

	result = NULL;
	while (list != NULL)
	{
		args = args_make(&list);
		// redirection handling 필요
		builtin(args, envp, &result);
		if (result == NULL)
			simple_command(args, envp, &result);
		// 리다이렉션, 파이프가 있다면 result를 특정한 곳으로 보냄
		// list
		// else
		args_free(&args);
	}
}
