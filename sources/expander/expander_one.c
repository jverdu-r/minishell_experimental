/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:06:57 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/16 19:09:38 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_cmd(t_command *raw_cmd, char **env)
{
	t_command	*cmd;
	char		*aux;

	cmd = raw_cmd;
	aux = split_words(raw_cmd->cmd, env);
	free(raw_cmd->cmd);
	cmd->cmd = aux;
}

void	expander(t_toolbox *tools)
{
	t_command	*cmd;

	cmd = tools->cmd;
	while (cmd)
	{
		check_cmd(cmd, tools->env);
		cmd = cmd->next;
	}
}
