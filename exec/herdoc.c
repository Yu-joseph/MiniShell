/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:51:16 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/14 23:27:41 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	run_herdoc(t_minishel *data)
{
	int			x;
	t_command	*cmd;

	x = 0;
	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->herdoc)
		{
			if (ft_her_doc(data, cmd, x++) == false)
			{
				free_old_data(data);
				data->exit_status = 1;
				return (false);
			}
		}
		cmd = cmd->next;
	}
	return (true);
}

void	if_multi_herdoc(t_command *cmd)
{
	t_herdoc	*herd;
	int			index;
	int			fd;

	fd = -1;
	index = arg_count(cmd->hr_file) - 1;
	herd = cmd->herdoc;
	while (herd && herd->next)
		herd = herd->next;
	fd = open(cmd->hr_file[index], O_RDONLY, 0600);
	if (fd == -1)
		perror("open");
	if (cmd->last_input == HERE_DOC)
		dup2(fd, STDIN_FILENO);
	close(fd);
}

bool	free_file_of_herd(t_minishel *data)
{
	t_command	*cmd;
	int			i;

	cmd = data->cmd;
	while (cmd)
	{
		i = 0;
		if (cmd->herdoc)
		{
			while (cmd->hr_file[i])
			{
				if (access(cmd->hr_file[i], F_OK) == 0)
					unlink(cmd->hr_file[i++]);
			}
		}
		cmd = cmd->next;
	}
	data->exit_status = 1;
	return (false);
}

void	clean_after_signal(char **files)
{
	int	i;
	int	fd;

	i = 0;
	if (!files)
		return ;
	while (files[i])
	{
		fd = open(files[i], O_TRUNC, 0644);
		close(fd);
		i++;
	}
}

void	fill_herd(t_minishel *data, int fd, t_herdoc *her_doc)
{
	char	*line;
	char	*tmp;
	t_help	help;

	line = readline("> ");
	while (ft_strcmp(line, (her_doc)->delimiter) != 0)
	{
		init_help(&help);
		if (!line)
			break ;
		if ((her_doc)->exp == true && ft_strchr(line, '$'))
		{
			tmp = line;
			line = exp_herdoc(line, data, &help);
			free(tmp);
			tmp = NULL;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	line = NULL;
}

bool	ft_her_doc(t_minishel *data, t_command *cmd, int count)
{
	t_herdoc	*her_doc;
	int			i;
	int			fd;
	int			cid;

	i = 0;
	her_doc = cmd->herdoc;
	if (store_file_name(cmd, count) == false)
	{
		free_d_array(cmd->hr_file);
		data->exit_status = 1;
		return (false);
	}
	while (her_doc && g_sig != SIGINT)
	{
		fd = reserve_for_herdoc(file_path(i++, count));
		if (fd < 0)
			return (free_d_array(cmd->hr_file), free_file_of_herd(data));
		if ((cid = fork()) == -1)
		{
			perror("fork");
			return false;
		}
		g_sig = -11;
		if (cid == 0)
		{
			signal(SIGINT, child_handler);
			fill_herd(data, fd, her_doc);
			exit(0);
		}
		else if (cid != 0)
		{
			if (g_sig == SIGINT)
			{
				clean_after_signal(cmd->hr_file);
				if (cmd->hr_file)
					free_d_array(cmd->hr_file);
				kill(cid, SIGINT);
				break ;
			}
			waitpid(cid, NULL, 0);
			close(fd);
			her_doc = her_doc->next;
		if (g_sig == SIGINT)
		{
			free_d_array(cmd->hr_file);
			g_sig = 0;
			return (false);
		}
		}
	}
	return (true);
}
