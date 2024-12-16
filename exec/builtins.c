/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:16:01 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/14 22:54:17 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtins(t_minishel *data, t_command *cmd, t_type stat)
{
	if (stat == complex)
	{
		manage_precedence(data, cmd);
		is_builtin(data, cmd);
		cleann_exec(data, cmd, NAME, clean);
		exit(EXIT_SUCCESS);
	}
	else if (stat == simple)
	{
		if (cmd->redirect != NULL)
		{
			cmd->prv_fd[0] = dup(STDOUT_FILENO);
			if (ft_redirection(cmd) < 0)
			{
				data->exit_status = 1;
				free(cmd->prv_fd);
				write(2, "minishell: ambiguous redirect\n", 30);
				return (free_old_data(data));
			}
			redirect_to(cmd);
		}
		is_builtin(data, data->cmd);
		cleann_exec(data, cmd, built, clean);
	}
}

void	is_builtin(t_minishel *data, t_command *cmd)
{
	if (!cmd)
		return ;
	if (!cmd->command || cmd->command[0] == '\0')
		return ;
	if (ft_strcmp(cmd->command, "cd") == 0)
		built_cd(data, cmd);
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		built_pwd();
	else if (ft_strcmp(cmd->command, "export") == 0)
		built_export(data, cmd);
	else if (ft_strcmp(cmd->command, "env") == 0)
		built_env(data);
	else if (ft_strcmp(cmd->command, "unset") == 0)
		built_unset(data, cmd->argument);
	else if (ft_strcmp(cmd->command, "echo") == 0)
		built_echo(cmd);
	else if (ft_strcmp(cmd->command, "exit") == 0)
		built_exit(data, cmd);
}

bool	check_if_builtins(t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (false);
	if (ft_strcmp(cmd->command, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->command, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->command, "export") == 0)
		return (true);
	if (ft_strcmp(cmd->command, "env") == 0)
		return (true);
	if (ft_strcmp(cmd->command, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->command, "exit") == 0)
		return (true);
	if (ft_strcmp(cmd->command, "unset") == 0)
		return (true);
	return (false);
}

void	builtin_exe(t_command *cmd, int **pip, int i, t_minishel *data)
{
	signals_hand(child);
	if (check_if_builtins(cmd) == true)
	{
		synch_pipe(pip, i, (get_count_cmd(data->cmd)), cmd);
		run_builtins(data, cmd, complex);
	}
	manage_precedence(data, cmd);
	synch_pipe(pip, i, (get_count_cmd(data->cmd)), cmd);
}
