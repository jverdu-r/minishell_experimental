/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:33:17 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/23 18:48:34 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_search(t_toolbox *tools)
{
	int	i;

	i = 0;
	while (tools->env[i])
	{
		if (!ft_strncmp(tools->env[i], "PWD=", 4))
			tools->pwd = ft_substr(tools->env[i],
					4, ft_strlen(tools->env[i]) - 4);
		if (!ft_strncmp(tools->env[i], "OLDPWD=", 7))
			tools->old_pwd = ft_substr(tools->env[i],
					7, ft_strlen(tools->env[i]) - 7);
		if (!ft_strncmp(tools->env[i], "HOME=", 5))
			tools->home_dir = ft_substr(tools->env[i],
					5, ft_strlen(tools->env[i] - 5));
		i++;
	}
	return (i);
}

char	*get_home(void)
{
	char 	*dir;
	char 	*home;
	int		i;
	int		ct;

	dir = getcwd(NULL, 0);
	i = 0;
	ct = 0;
	while (dir[i] && ct <=2)
	{
		if (dir[i] == '/')
			ct++;
		i++;
	}
	home = ft_strjoin("HOME=", ft_substr(dir, 0, i));
	return (home);
}
char	**new_env(void)
{
	char **env;

	env = ft_calloc(sizeof(char *), 4);
	env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	env[1] = get_home();
	env[3] = 0;
	return (env);
}

char	**st_envp(char **envp)
{
	char	**sorted;
	char	*aux;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	sorted = ft_calloc(sizeof(char *), i + 1);
	if (!sorted)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		sorted[i] = envp[i];
		i++;
	}
	sorted[i] = 0;
	i = 0;
	while (sorted[i])
	{
		j = i + 1;
		while (sorted[j])
		{
			if (ft_strcmp(sorted[i], sorted[j]) > 0)
			{
				aux = sorted[j];
				sorted[j] = sorted[i];
				sorted[i] = aux;
			}
			j++;
		}
		i++;
	}
	return (sorted);
}

void	show_env(t_toolbox *tools)
{
	int	i;

	i = 0;
	printf("\n---unsorted env---\n");
	while (tools->env[i])
	{
		printf("%s\n", tools->env[i]);
		i++;
	}
	i = 0;
	printf("\n---sorted env---\n");
	while (tools->sort_env[i])
	{
		printf("%s\n", tools->sort_env[i]);
		i++;
	}
}

char	**envp_dup(char	**envp, t_toolbox *tools)
{
	char	**tmp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	tmp = ft_calloc(sizeof(char *), i + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		if (!tmp[i])
		{
			free_arr(tmp);
			return (NULL);
		}
		i++;
	}
	tools->env = tmp;
	return (tmp);
}
