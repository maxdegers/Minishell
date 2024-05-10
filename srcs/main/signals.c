/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:17:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/10 20:02:17 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_signal(void)
{
	signal(SIGINT, ft_handle_sig);
	signal(SIGQUIT, ft_handle_sig);
}

void	ft_set_signal_child(void)
{
	signal(SIGINT, ft_handle_sig_child);
	signal(SIGQUIT, ft_handle_sig_child);
}

void	ft_handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		(void)sig;
	}
}

void	ft_handle_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
	}
	if (sig == SIGQUIT)
	{
		(void)sig;
	}
}
