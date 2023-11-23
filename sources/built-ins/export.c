/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:51:30 by davidaparic       #+#    #+#             */
/*   Updated: 2023/11/23 18:47:40 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(char **env)
{
	int	i;
	int	k;

	i = 0;
	while (env[i])
	{
		k = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (env[i][k])
		{
			ft_putchar_fd(env[i][k], STDOUT_FILENO);
			if (env[i][k++] == '=')
				ft_putchar_fd('\"', STDOUT_FILENO);
		}
		if (ft_strchr(env[i], '='))
			ft_putchar_fd('\"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	free(env);
}

char	**add_variable(char **sort_env, char *cmd_arg)
{
	int		i;
	char	**copy_env;

	i = 0;
	while (sort_env[i])
		i++;
	copy_env = ft_calloc(i + 2, sizeof(char *));
	if (!copy_env)
		return (NULL);
	i = 0;
	while (sort_env[i])
	{
		if (!sort_env[i + 1])
		{
			copy_env[i] = sort_env[i];
			copy_env[i + 1] = ft_strdup(cmd_arg);
			copy_env[i + 2] = 0;
		}
		else
			copy_env[i] = sort_env[i];
		i++;
	}
	return (copy_env);
}

void	ft_export(t_toolbox *tools)
{
	int		i;
	char	**tmp;

	i = 0;
	if (tools->cmd->args == NULL)
		print_export(st_envp(tools->env));
	else
	{
		while (tools->cmd->args[i])
		{
			if (!check_parametres(tools->cmd->args[i])
				&& !check_variable_exist(tools, tools->cmd->args[i]))
			{
				if (tools->cmd->args[i])
				{
					tmp = add_variable(tools->env, tools->cmd->args[i]);
					free(tools->env);
					tools->env = tmp;
				}
			}
			i++;
		}
	}
}
