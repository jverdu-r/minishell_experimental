/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:57:59 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/24 17:58:01 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_search(char **gvars, char *var)
{
	int	pos;

	pos = 0;
	while (gvars[pos])
	{
		if (ft_strnstr(gvars[pos], var, ft_strlen(var)))
			return (pos);
		pos++;
	}
	return (-1);
}

char	*extract_var(char **vars, char *str)
{
	int		part;
	int		var_pos;
	char	*var;
	char	**s_var;

	part = 1;
	var = ft_strjoin(ft_substr(str, 1, ft_strlen(str) - 1), '=');
	var_pos = var_search(vars, var);
	if (var_pos >= 0)
	{
		s_var = ft_split(vars[var_pos], '=');
		free(var);
		var = ft_strdup(s_var[part]);
		free_arr(s_var);
		return (var);
	}
	else
		return (NULL);
}

char    *paste_str(t_exp *list, char **env)
{
    char    *str;

    str = NULL;
    while (list)
    {
        if (list->exp == '$')
            str = ft_strjoin(str, extract_var(env, list->str));
        else
            str = ft_strjoin(str, list->str);
        list = list->next;
    }
    return (str);
}

char    *expand(char *str, char **env)
{
    t_exp   *list;
    int     i;
    int     j;

    list = NULL;
    i = 0;
    while(str[i])
    {
        if (str[i] == '$')
        {
            j = 0;
            while (str[i + j] != ' ' || str[i + j + 1] == '$' && str[i + j])
                j++;
            exp_lst_addback(&list, exp_new(ft_substr(str, i, j), str[i]));
            i += j;
        }
        if (str[i] != '$')
        {
            j = 0;
            while (str[i + j] != '$' && str[i + j])
                j++;
            exp_lst_addback(&list, exp_new(ft_substr(str, i, j), 'n'));
            i += j;
        }
    }
    return (paste_str(list, env));
}
char    *expansor(t_exp *list, char **env)
{
    char *str;

    while (list)
    {
        if (list->exp == '\"')
            list->str = expand(list->str, env);
        list = list->next;
    }
    while (list->prev)
        list = list->prev;
    str = list->str;
    list = list->next;
    while (list->next)
    {
        str = ft_strjoin(str, list->str);
        list = list->next;
    }
    return (str);
}

char   *check_exp(char *str, char **env)
{
    t_exp   *list;
    int     i;
    int     j;

    list = NULL;
    i = 0;
    while(str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            j = 0;
            while (str[i + j] != str[i] && str[i + j] && str[i + j])
                j++;
            exp_lst_addback(&list, exp_new(ft_substr(str, i, j), str[i]));
            i += j;
        }
        if (str[i] != '\'' && str[i] != '\"')
        {
            j = 0;
            while (str[i] != '\'' && str[i] != '\"' && str[i + j])
                j++;
            exp_lst_addback(&list, exp_new(ft_substr(str, i, j), 'n'));
            i += j;
        }
    }
    return (expansor(list, env));
}

void    *expander(t_command *cmd, t_toolbox *tools)
{
    while (cmd)
    {
        cmd->cmd = check_exp(cmd->cmd, tools->env);
        cmd = cmd->next;
    }
}