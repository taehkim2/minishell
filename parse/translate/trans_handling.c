/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:41:25 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/11 19:14:23 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trans_quoted_remove(char **token)
{
	char	*removed_token;
	char	quote;
	int		removed_idx;
	int		idx;

	removed_idx = 0;
	idx = 0;
	removed_token = malloc(ft_strlen(*token) + 1);
	if (removed_token == NULL)
		error_end("malloc failed");
	while ((*token)[idx] != '\0')
	{
		if (is_quoted(*token, idx, '\'') || is_quoted(*token, idx, '\"'))
		{
			quote = (*token)[idx++];
			while ((*token)[idx] != quote)
				removed_token[removed_idx++] = (*token)[idx++];
			idx++;
		}
		else
			removed_token[removed_idx++] = (*token)[idx++];
	}
	removed_token[removed_idx] = '\0';
	free(*token);
	*token = removed_token;
}

char	*trans_param_expansion(char *token, char **envp)
{
	char	**splited_token;
	char	*expansed_token;
	int		idx;

	idx = 0;
	splited_token = expansion_token_split(token);
	expansion_dollar_convert(&splited_token, envp);
	expansed_token = expansion_token_merge(splited_token);
	while (splited_token[idx] != NULL)
		free(splited_token[idx++]);
	free(splited_token);
	return (expansed_token);
}
