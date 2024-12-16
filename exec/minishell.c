/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:41:14 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/12 14:19:50 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node(t_env **head, t_env *new)
{
	t_env	*temp;

	if (!head || !new)
		return ;
	temp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;
}

t_env	*create_node(char *content)
{
	t_env	*node;
	char	*name;
	char	*value;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(EXIT_FAILURE);
	name = extract_str(content, NAME);
	value = extract_str(content, VALUE);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	set_env(t_minishel *data, char **ev)
{
	int	i;

	i = 0;
	data->env = create_node(ev[i]);
	while (ev[++i])
		add_node(&data->env, create_node(ev[i]));
}
