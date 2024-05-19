/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:03:38 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/07 16:04:55 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close2(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	close3(int fd1, int fd2, int fd3)
{
	close(fd1);
	close(fd2);
	close(fd3);
}

void	close4(int fd1, int fd2, int fd3, int fd4)
{
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
}

void	ft_close_useless_fds(int **fds, int *used, size_t pipe_amount)
{
	size_t	i;

	i = -1;
	if (!used)
	{
		while (++i < pipe_amount)
			close2(fds[i][0], fds[i][1]);
		return ;
	}
	while (++i < pipe_amount)
	{
		if (fds[i][0] != used[0] && fds[i][0] != used[1])
			close(fds[i][0]);
		if (fds[i][1] != used[0] && fds[i][1] != used[1])
			close(fds[i][1]);
	}
}

void	ft_close_heredoc_pipe(t_data *data)
{
	t_block	*block;
	t_redir	*redir;

	block = data->block;
	while (block)
	{
		redir = block->redir;
		while (redir)
		{
			if (redir->fd != -1)
				close(redir->fd);
			redir = redir->next;
		}
		block = block->next;
	}
}
