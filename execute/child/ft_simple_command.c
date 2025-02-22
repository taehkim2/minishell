/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:52:44 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/20 13:15:45 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_minishell(char *command)
{
	if (ft_strncmp(command, "./minishell", 12) == 0)
		return (1);
	return (0);
}

char	*make_path(char *path, char *filename)
{
	char	*result;
	int		path_len;
	int		filename_len;

	path_len = ft_strlen(path);
	filename_len = ft_strlen(filename);
	result = malloc(sizeof(char) * (path_len + filename_len + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, path, path_len + 1);
	result[path_len] = '/';
	ft_strlcpy(result + path_len + 1, filename, filename_len + 1);
	return (result);
}

char	*get_external_path(char *command, char **envp)
{
	char	*found;
	int		table_idx;
	char	*path;
	char	**path_table;
	char	current_path[BUFSIZ];

	found = NULL;
	table_idx = -1;
	path = ft_getenv("PATH", envp);
	path_table = ft_split(path, ':');
	if (path != NULL)
		free(path);
	path = getcwd(current_path, BUFSIZ);
	while (path_table[++table_idx] != NULL)
	{
		chdir(path_table[table_idx]);
		if (access(command, F_OK) == 0)
		{
			found = make_path(path_table[table_idx], command);
			break ;
		}
	}
	my_free2(path_table);
	chdir(path);
	return (found);
}

void	simple_command(char **args, char **envp)
{
	char	*command;
	char	*filename;
	char	*path;

	if (ft_strchr(args[0], '/') != NULL)
		filename = get_filename(args[0]);
	else
		filename = args[0];
	path = get_path(args[0]);
	if ((path != NULL) && is_it_path(args[0], path, filename))
		command = args[0];
	else
		command = get_external_path(filename, envp);
	execve(command, args, envp);
}
