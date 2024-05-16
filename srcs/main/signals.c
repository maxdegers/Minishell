/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:17:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/11 15:06:23 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_signal(t_SIG_MODE mode)
{
	if (mode == SIG_MAIN)
		signal(SIGINT, &ft_handle_sig);
	else if (mode == SIG_CHILD)
		signal(SIGINT, &ft_handle_sig_child);
	signal(SIGQUIT, &ft_handle_sig);
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
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handle_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
//		ft_putstr_fd("\n", 2);
	}
}
