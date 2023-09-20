/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:17:51 by daparici          #+#    #+#             */
/*   Updated: 2023/09/09 17:57:10 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_arguments(char **arg, int i)
{
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

void	ft_echo(t_sp_cmds *sp_cmds)
{
	int		flag;
	size_t	i;
	size_t	j;

	flag = 0;
	i = 1;
	while (sp_cmds->cmd[i] && !ft_strncmp(sp_cmds->cmd[i], "-n", 2))
	{
		j = 1;
		while (sp_cmds->cmd[i][j] && sp_cmds->cmd[i][j] == 'n')
			j++;
		if (j != ft_strlen(sp_cmds->cmd[i]) && sp_cmds->cmd[i][j] != 'n')
			break ;
		flag = 1;
		i++;
	}
	if (sp_cmds->cmd[i])
		print_arguments(sp_cmds->cmd, i);
	if (flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
