/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/23 11:48:52 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_print(t_list *list)
{
	int	new_flgs;

	while (list != NULL)
	{
		new_flgs = get_flags(list);
		printf("token : %s\n", get_token(list));
		if (list->info.flgs & F_QUOTED)
			printf("F_QUOTED is on\n");
		if (list->info.flgs & F_NOT_QUOTED)
			printf("F_NOT_QUOTED is on\n");
		if (list->info.flgs & F_LESS)
			printf("F_LESS flag is on\n");
		if (list->info.flgs & F_DLESS)
			printf("F_DLESS flag is on\n");
		if (list->info.flgs & F_GRATE)
			printf("F_GRATE flag is on\n");
		if (list->info.flgs & F_DGRATE)
			printf("F_DGRATE flag is on\n");
		if (list->info.flgs & F_PIPE)
			printf("F_PIPE flag is on\n");
		if (list->info.flgs & F_DOLLAR)
			printf("F_DOLLAR flag is on\n");
		if (list->info.flgs & F_STRING)
			printf("F_STRING flag is on\n");
		list = list->next;
	}
}

// void	export(char ***envp)
// {
// 	int	idx;

// 	idx = 0;
// 	while ((*envp)[idx] != NULL)
// 		idx++;
// 	(*envp)[idx] = "asdf";
// 	(*envp)[idx] = NULL;
// }

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*list;

	while (1)
	{
		line = readline("minishell$ ");
		if (ft_strchr(line, '\n'))
			printf("is has \\n\n");
		if (line == NULL)
			error_end("readline failed");
		if (line[0])
		{
			add_history(line);
			list = parse(line, envp);
			list_print(list);
			list_free(&list);
		}
		free(line);
	}
}
// ?!!! 왜 공백만 들어가면 모든 플래그가 켜지는가?