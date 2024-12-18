/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:40:41 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/14 14:09:18 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		exit(0);
	}
	if (sig == SIGQUIT)
	{
		exit(131);
	}
}
