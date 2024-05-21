/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:17:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/20 18:07:51 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_signal(t_SIG_MODE mode)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (mode == SIG_MAIN)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_handle_sig);
	}
	else if (mode == SIG_CHILD)
	{
		signal(SIGQUIT, &ft_handle_sig_child);
		signal(SIGINT, &ft_handle_sig_child);
	}
	else if (mode == SIG_HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_handle_sig_heredoc);
	}
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
}

void	ft_handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_handle_sig_child(int sig)
{
	if (sig == SIGINT)
		g_error = 130;
	if (sig == SIGQUIT)
	{
		g_error = 131;
		ft_putstr_fd("Quit (core dumped)\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
