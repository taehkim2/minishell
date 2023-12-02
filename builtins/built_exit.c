/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:24:56 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/01 20:21:19 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	my_exit(char **argv)
{
	int		argv_idx;

	argv_idx = 1;
	if (argv[argv_idx] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
}
