/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:57:24 by mait-taj          #+#    #+#             */
/*   Updated: 2024/11/26 12:19:18 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	close_pipfd(t_pipe **tube)
// {
// 	t_pipe	*tmp;

// 	tmp = *tube;
// 	while (tmp && tmp->next)
// 	{
// 		// if (tmp->pipfd[0] && tmp->pipfd[1])
// 		// {
// 			if (tmp->pipfd[0] != -1)
// 				close(tmp->pipfd[0]);
// 			if (tmp->pipfd[1] != -1)
// 				close(tmp->pipfd[1]);
// 			// if (tmp->pipfd)
// 			free(tmp->pipfd);
// 		// }
// 		tmp = tmp->next;
// 	}
// }

// t_pipe	*creat_pipe()
// {
// 	t_pipe	*head;

// 	head = malloc(sizeof(t_pipe));
// 	if (!head)
// 		handl_error("malloc");
// 	head->pipfd = malloc(sizeof(int) * 2);
// 	if (!head->pipfd)
// 		handl_error("malloc");
// 	head->pipfd[0] = -1;
// 	head->pipfd[1] = -1;
// 	head->next = NULL;
// 	head->prev = NULL;
// 	return (head);
// }

// void	add_pipe(t_pipe **head, t_pipe *new)
// {
// 	t_pipe	*tmp;
// 	t_pipe	*cur;

// 	tmp = *head;
// 	if ((*head)->next == NULL)
// 	{
// 		(*head)->next = new;
// 		new->prev = *head;
// 		return ;
// 	}
// 	cur = (*head)->next;
// 	while (tmp && tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// 	new->prev = tmp;
// }
// void	init_pipe(t_minishel *data, int size)
// {
// 	t_pipe	*tmp;
// 	int	i;

// 	i = -1;
// 	if (size == 1)
// 	{
// 		data->pie = creat_pipe();
// 		if (pipe(data->pie->pipfd) == -1)
// 			handl_error("pipe");
// 		return ;
// 	}
// 	data->pie = creat_pipe();
// 	while (++i < size - 1)
// 		add_pipe(&data->pie, creat_pipe());
// 	tmp = data->pie;
// 	while (tmp)
// 	{
// 		if (pipe(tmp->pipfd) == -1)
// 			handl_error("pipe");
// 		tmp = tmp->next;
// 	}
// }
