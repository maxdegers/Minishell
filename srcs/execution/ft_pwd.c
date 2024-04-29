/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:40:09 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/26 12:10:39 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear_fd_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (tmp)
	{
		tmp->fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC);
		if (tmp->fd == -1)
			return (-1);
	}
}

void	ft_pwd(t_block *block, t_data *data, int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf_fd(fd, "%s\n", pwd);
	free(pwd);
}
