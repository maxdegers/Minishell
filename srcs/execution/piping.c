/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:52:40 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/19 23:56:51 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_pipe_amount(t_block *block)
{
	size_t	i;
	t_block	*tmp;

	i = 0;
	tmp = block;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (--i);
}

int	**malloc_fd_tab(size_t size)
{
	int		**fd;
	size_t	i;

	fd = malloc(sizeof(int *) * (size + 1));
	if (!fd)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			while (--i)
				free(fd[i]);
			free(fd);
			return (NULL);
		}
	}
	return (fd);
}

int	ft_get_fd(int **fds, size_t i, int *res, size_t pipe_amount)
{
	if (pipe_amount == 0)
		return (res[0] = 0, res[1] = 1, 0);
	if (i == 0)
		res[0] = 0;
	else
		res[0] = fds[i - 1][0];
	if (i == pipe_amount)
		res[1] = 1;
	else
		res[1] = fds[i][1];
	ft_close_useless_fds(fds, res, pipe_amount);
	return (0);
}

int	**ft_open_pipes(t_data *data, size_t pipe_amount)
{
	int		**fd;
	size_t	i;

	fd = malloc_fd_tab(pipe_amount);
	if (!fd)
		exit_error(ERROR_MALLOC, NULL, data);
	i = 0;
	while (i < pipe_amount)
	{
		if (pipe(fd[i]) == -1)
		{
			while (--i)
				close2(fd[i][0], fd[i][1]);
			exit_error(ERROR_PIPE, NULL, data);
		}
		i++;
	}
	fd[i] = NULL;
	return (fd);
}
