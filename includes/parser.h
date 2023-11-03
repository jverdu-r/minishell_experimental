/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:45 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/03 17:13:21 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "libft/libft.h"
#include "tokens.h"
#include "structs.h"
#include "minishell.h"

t_command	*parser(t_toolbox *tools);
int			token_reader(t_toolbox *tools);
int			token_handler(t_toolbox *tools, int i);
t_token		check_token(char *tk, int i);
char		*fully_prompt(char *input, char c);
t_redir     *redir_new(char *str);
void        redir_addback(t_redir **head, t_redir *new);
void        redir_show(t_redir *list, char *str);
void        redir_free(t_redir *redir);
void	    cmd_show(t_command *cmd);
void	    cmd_free(t_command *cmd);
void        get_fds(t_command *cmd);
#endif
