/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:06:49 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/14 23:03:56 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*last_check(t_minishel *data)
{
	char	*path;

	path = check_cmd_path(data, data->cmd->command);
	if (!path)
	{
		free_old_data(data);
		exit(data->exit_status);
	}
	return (path);
}

void	check_open_herd(t_minishel *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->herdoc)
		{
			unlink_files(cmd->hr_file);
			free_d_array(cmd->hr_file);
		}
		cmd = cmd->next;
	}
}

bool	save_prv_fd(t_command *cmd)
{
	if (check_if_builtins(cmd) == false)
		return (true);
	if (!cmd->redirect)
		return (true);
	cmd->prv_fd = malloc(sizeof(int));
	if (!cmd->prv_fd)
		return (false);
	return (true);
}
