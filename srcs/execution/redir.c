/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:18:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/02 14:46:59 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_error(t_block *block)
{
	t_redir		*tmp;

	tmp = block->redir;
	while (tmp)
	{
		if (tmp->fd != -1)
			close(tmp->fd);
		tmp = tmp->next;
	}
}

static char	*ft_open_redir(t_block *block)
{
	t_redir		*tmp;

	tmp = block->redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			tmp->fd = open(tmp->file, O_RDONLY);
		if (tmp->type == REDIR_OUT)
			tmp->fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp->type == REDIR_APPEND)
			tmp->fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp->fd == -1)
			return (ft_close_error(block), tmp->file);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	ft_get_redirs(t_block *block, int *in, int *out)
{
	t_redir		*tmp;

	tmp = block->redir;
	*in = -1;
	*out = -1;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT)
			*out = tmp->fd;
		if (tmp->type == REDIR_APPEND)
			*out = tmp->fd;
		if (tmp->type == REDIR_IN)
			*in = tmp->fd;
		if (tmp->type == REDIR_HEREDOC)
			*in = tmp->fd;
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_redir(t_block *block, int *fd)
{
	int		in;
	int		out;
	char	*ret;

	ret = ft_open_redir(block);
	if (ret)
		return (ret);
	ft_get_redirs(block, &in, &out);
	if (in != -1)
		fd[0] = in;
	if (out != -1)
		fd[1] = out;
	return (NULL);
}
