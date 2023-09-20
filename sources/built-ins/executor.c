/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:02 by daparici          #+#    #+#             */
/*   Updated: 2023/09/09 17:57:53 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_sp_cmds *exec_list, t_toolbox *tools)
{
	int	exit;

	exit = 0;
	(void)tools;
	while (exec_list)
	{
		if (ft_strcmp(exec_list->cmd[0], "pwd") == 0)
			exit = ft_pwd();
		if (ft_strcmp(exec_list->cmd[0], "echo") == 0)
			ft_echo(exec_list);
		exec_list = exec_list->next;
	}
}
