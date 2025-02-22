/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:13:03 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/15 14:57:08 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *command)
{
	int		command_len;
	char	*path;

	command_len = ft_strlen(command);
	while (command_len > 0 && command[command_len] != '/')
		command_len--;
	if (command_len == 0)
		return (NULL);
	path = malloc(sizeof(char) * (command_len + 1));
	if (!path)
		error_end("malloc failed");
	ft_strlcpy(path, command, command_len + 1);
	return (path);
}

char	*get_filename(char *command)
{
	int		command_len;
	char	*filename;

	command_len = ft_strlen(command);
	while (command_len > 0 && command[command_len] != '/')
		command_len--;
	if (command_len == 0)
		return (NULL);
	filename = malloc(sizeof(char) * (ft_strlen(command) - command_len + 1));
	if (!filename)
		return (NULL);
	ft_strlcpy(filename, command + command_len + 1, \
				ft_strlen(command) - command_len);
	return (filename);
}
