/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:02 by daparici          #+#    #+#             */
/*   Updated: 2023/11/23 18:34:41 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_toolbox *tools)
{
	int			exit;
	t_command	*cmd;

	exit = 0;
	cmd = tools->cmd;
	while (cmd)
	{
		if (ft_strcmp(cmd->cmd, "pwd") == 0)
			exit = ft_pwd();
		if (ft_strcmp(cmd->cmd, "echo") == 0)
			ft_echo(cmd);
		if (ft_strcmp(cmd->cmd, "env") == 0)
			ft_env(tools->env);
		if (ft_strcmp(cmd->cmd, "export") == 0)
			ft_export(tools);
		cmd = cmd->next;
	}
}
