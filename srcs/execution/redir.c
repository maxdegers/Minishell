/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:18:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/08 10:55:15 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_error(t_block *block)
{
	t_redir		*tmp;

	tmp = block->redir;
	while (tmp && tmp->fd != -1)
	{
		close(tmp->fd);
		tmp = tmp->next;
	}
}

int	ft_open_redir(t_block *block)
{
	t_redir		*tmp;

	tmp = block->redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			tmp->fd = open(tmp->file, O_RDONLY);
		if (tmp->type == REDIR_OUT)
			tmp->fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC,
						S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
		if (tmp->type == REDIR_APPEND)
			tmp->fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND,
						S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
		if (tmp->type == REDIR_HEREDOC)
			tmp->fd = open(tmp->file, O_RDONLY);
		if (tmp->fd == -1)
			return (ft_close_error(block), 1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_get_redirs(t_block *block, int *in, int *out)
{
	t_redir		*tmp;

	tmp = block->redir;
	*in = -1;
	*out = -1;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT)
			*out = tmp->fd;
		if (tmp->type == REDIR_IN)
			*in = tmp->fd;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_redir(t_block *block, int *fd)
{
	int		in;
	int		out;

	if (ft_open_redir(block))
		return (1);
	ft_get_redirs(block, &in, &out);
	if (in != -1)
		fd[0] = in;
	if (out != -1)
		fd[1] = out;
	return (0);
}
