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
