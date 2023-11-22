/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:16:01 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/22 15:01:20 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

# include "../libft/libft.h"

typedef struct s_token_info
{
	char	*token;
	int		flgs;
}	t_token_info;

typedef struct s_list
{
	struct s_list	*next;
	t_token_info	info;
}	t_list;

# define NOT_QUOTED			0
# define QUOTED				1

# define NEXT				0
# define END				1

# define START				-1
# define F_QUOTED			2
# define F_NOT_QUOTED		4
# define F_PIPE	     		8
# define F_DOLLAR			16
# define F_STRING      		32
# define F_GRATE			64
# define F_DGRATE			128
# define F_LESS				256
# define F_DLESS			512

void	error_end(char *str);
void	token_add(t_list **list, char *new_token, int new_flags);
int		get_flags(t_list *list);
char	*get_token(t_list *list);
void	list_node_add(t_list **list);
t_list	*list_init(t_list **list);
void	list_free(t_list **list);
void	parse(t_list **list, char *line);
void	token_flgs(t_list **list, int *new_flgs, char *buf);
int		token_rules(t_list **list, char **buf, char now_char);
void	token_delimited(t_list **list, char **buf);
int		flgs_redirection(char *buf, int *new_flgs);
int		flgs_pipe(char *buf, int *new_flgs);
int		flgs_dollar(char *buf, int *new_flgs);
int		flgs_quote(char *buf, int *new_flgs);
void	flgs_quote_dollar(char *buf, int *new_flgs);
int		rules_operator_double(char **buf, char now_char);
int		rules_operator_end(char **buf, char now_char);
int		rules_operator_start(char **buf, char now_char);
int		rules_space(char **buf, char now_char);
int		rules_comment(char **buf, char now_char);
int		quote_check(char *buf);
int		operator_check(char prev_char);

#endif
