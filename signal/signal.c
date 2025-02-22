/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:16:11 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/15 11:12:51 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_mode(void)
{
	signal(SIGQUIT, sigquit_print_quit);
	signal(SIGINT, sigint_print_newline);
}

void	heredoc_mode(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_print_newline);
}

void	interactive_mode(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_print_rl);
}

void	line_creat_mode(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_print_newline);
}
