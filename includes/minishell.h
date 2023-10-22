/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:07:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/09 10:59:57 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "tokens.h"
#include "structs.h"

//test
t_command   *cmd_extract(t_lexer *list);
int check_syntax(t_lexer *tk_list);

//signal functions
void	signals_workout(void);

//t_lexer functions

void	lexer_addback(t_lexer **head, t_lexer *new);
void	lexer_add(t_lexer **head, t_lexer *new);
void	lexer_delone(t_lexer **list);
void	lexer_free(t_lexer *list);
void	lexer_show(t_lexer *list); //free list only for testting
int		lexer_length(t_lexer *list);
t_lexer	*lexer_new(char	*str, t_token token);
t_lexer	*lexer_last(t_lexer *list);

//t_sp_cmds functions
void		sp_cmds_addback(t_sp_cmds **head, t_sp_cmds *new);
void		sp_cmds_add(t_sp_cmds **head, t_sp_cmds *new);
void		sp_cmds_delone(t_sp_cmds **list);
void		sp_cmds_free(t_sp_cmds *list);
void		sp_cmds_show(t_sp_cmds *list); //frees list  only for testing
int			sp_cmds_length(t_sp_cmds *list);
t_sp_cmds	*sp_cmds_new(char **cmd, int token);
t_sp_cmds	*sp_cmds_last(t_sp_cmds *list);

//parse functions
t_sp_cmds	*parser(t_toolbox *tools);
int			file_checker(char *str);
int			token_reader(t_toolbox *tools);
int			token_handler(t_toolbox *tools, int i);
t_token		check_token(char *tk, int i);
void		check_exp(t_sp_cmds *node, t_toolbox *tools);
void		cmd_trim(t_sp_cmds *node);
char		*fully_prompt(char *input, char c);

//loop functions
int		minishell_loop(t_toolbox *tools);
int		tools_load(t_toolbox *tools);
void	tools_reload(t_toolbox *tools);

//enviroment functions
char	**envp_dup(char **envp, t_toolbox *tools);
//char	 **st_envp(t_toolbox *tools, char **env);
int		pwd_search(t_toolbox *tools);

//utility functions
char		*expander(t_toolbox *tools, char *str);
void		free_arr(char **arr);
int		handle_quotes(char *input);
int		check_input(t_toolbox *tools);
int		check_quotes(char *str);
int		exit_code(void);
t_bool switch_bool(t_bool bool);

//error functions
int		error_msg(char *msg);
int		error_token(t_token token);

//built-ins funcion
void	ft_executor(t_sp_cmds *exec_list, t_toolbox *tools);
//  echo
void	ft_echo(t_sp_cmds *sp_cmds);
void	print_arguments(char **arg, int i);
//  pwd
int		ft_pwd(void);
#endif
