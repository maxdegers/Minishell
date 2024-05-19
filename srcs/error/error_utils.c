/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:31:54 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/18 20:32:26 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_child(t_data *data, int **fds, int *fd)
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	ft_free_int_tab(fds);
	destroy(data);
	ft_megafree(data);
	exit(g_error);
}
