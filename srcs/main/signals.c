/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:17:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/10 21:08:46 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_signal(void)
{
	struct sigaction sig;

	sig.sa_handler = &ft_handle_sig;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	ft_set_signal_child(void)
{
	struct sigaction sig;

	sig.sa_handler = &ft_handle_sig_child;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
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
		(void)sig;
}

void	ft_handle_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
		ft_putstr_fd("\n", 2);
	}
	if (sig == SIGQUIT)
		(void)sig;
}
