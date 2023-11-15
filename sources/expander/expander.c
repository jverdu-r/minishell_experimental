/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:51:06 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/15 18:33:55 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     word_count(char *str)
{
    int     i;
    int     wd;
    t_bool  qt;

    if (!str)
        return(0);
    else
    {
        i = 0;
        wd = 1;
        qt = FALSE;
        while (str[i])
        {
            if (str[i] == '\'' || str[i] == '\"')
            {
                qt = switch_bool(qt);
                if (qt == TRUE)
                    wd++;
            }
            i++;
        }
        return(wd);
    }
}

char    **exp_words(char **words, char  **env)
{
    char    **arr;
    char    *aux;
    int     i;

    i = 0;
    while (words[i])
        i++;
    arr = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (words[i])
    {
        if (words[i][0] == '\"')
        {
            aux = ft_substr(words[i], 1, ft_strlen(words[i]) - 2);
            arr[i] = exp_word(aux, env);
            printf("postsubstr \": %s\n", arr[i]);
            i++;
        }
        else if (words[i][0] == '\'')
        {
            aux = ft_substr(words[i], 1, ft_strlen(words[i]) - 2);
            arr[i] = ft_strdup(aux);
            printf("postsubstr ': %s\n", arr[i]);
            i++;
        }
        else
        {
            aux = ft_strdup(words[i]);
            arr[i] = exp_word(aux, env);
            printf("postsubstr _: %s\n", arr[i]);
            i++;
        }
	}
        free(aux);
    return (arr);
}

int extract_qt(char *str, int i, char **words, int wd)
{
    int j;

    j = 1;
    while (str[i + j] != str[i] && str[i + j])
        j++;
    words[wd] = ft_substr(str, i, j + 1);
    return (i + j);
}

char    *split_words(char *str, char **env)
{
    char    **words;
    int     wd;
    int     i;
    int     j;

    i = 0;
    j = 0;
    wd = word_count(str);
    words = malloc(sizeof(char *) * (wd + 2));
    wd = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            i = extract_qt(str, i, words, wd);
            wd++;
        }
        else
        {
            j = 0;
            while (str[i + j])
            {
                if (str[i + j] == '\'' || str[i + j] == '\"')
                    break;
                j++;
            }
            words[wd] = ft_substr(str, i, j);
            if (str[i + j] == '\'' || str[i + j] == '\"')
                j--;
            wd++;
            i += j;
        }
        i++;
    }
    words[wd] = 0;
    words = exp_words(words, env);
    i = 0;
    while (words[i])
    {
        printf("word[%d]: %s\n", i, words[i]);
        i++;
    }
    return (arr_join(words));
}

void    check_cmd(t_command *raw_cmd, char **env)
{
    t_command   *cmd;
    char    *aux;

    cmd = raw_cmd;
    aux = split_words(raw_cmd->cmd, env);
    free(raw_cmd->cmd);
    cmd->cmd = aux;
    //cmd->cmd = exp_words(raw_cmd->cmd, env);
    //cmd->append = exp_words(raw_cmd->append, env);
    //cmd->limiter = exp_word(raw_cmd->limiter, env);
    /*cmd->args = exp_args(raw_cmd->args, env);
    cmd->in_files = exp_redir(raw_cmd->in_files, env);
    cmd->out_files = exp_redir(raw_cmd->out_files, env);*/
}

void    expander(t_toolbox *tools)
{
    t_command   *cmd;

    cmd = tools->cmd;
    while (cmd)
    {
        check_cmd(cmd, tools->env);
        cmd = cmd->next;
    }
}
