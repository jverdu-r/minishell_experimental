/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:54:39 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/24 18:54:42 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*arr_join(char **arr)
{
	int		i;
	char	*str;
	char	*aux;

	i = 1;
	str = ft_strdup(arr[0]);
	while (arr[i])
	{
		aux = str;
		str = ft_strjoin(aux, arr[i]);
		free(aux);
		i++;
	}
	return (str);
}

int		exp_count(char *str)
{
	int	i;
	int	wd;

	if (!str)
		return (0);
	i = 0;
	wd = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (str[i] == '$' && str[i])
				i++;
				wd++;
		}
		i++;
	}
	if (wd == 0)
		wd = 1;
	return (wd);
}

char	*expnd(char *str, char **env)
{
	char	*aux;
	char	**r_var;
	int		i;

	aux = ft_strjoin(str, "=");
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], aux, ft_strlen(aux)))
		{
			r_var = ft_split(env[i], '=');
			free(aux);
			aux = ft_strdup(r_var[1]);
			free_arr(r_var);
			return(aux);
		}
		i++;
	}
	return (NULL);
}

char    *exp_word(char *str, char **env)
{
    char    **arr;
    int     i;
	int		j;
    int		wd;

	i = 0;
	j = 0;
	wd = exp_count(str);
	arr = malloc(sizeof(char *) * (wd + 2));
	wd = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = 0;
			while (str[i] == '$' && str[i])
			{
				i++;
			}
			while (str[i + j])
			{
				if (str[i + j] == '$' || str[i + j] == ' ')
					break;
				j++;
			}
			arr[wd] = expnd(ft_substr(str, i, j), env);
			wd++;
			i += j;
		}
		else
		{
			j = 0;
			while (str[i + j] != '$' && str[i + j])
				j++;
			arr[wd] = ft_substr(str, i, j);
			wd++;
			i += j;
		}
		i++;
	}
	arr[wd] = 0;
	return (arr_join(arr));
}