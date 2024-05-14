/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:46:25 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/14 14:29:21 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait_childs(int *pid, size_t child_amount)
{
	size_t	i;
	int		ret_status;

	i = -1;
	while (++i < child_amount)
	{
		waitpid(pid[i], &ret_status, 0);	//TODO check les return error des childs
	}
//	g_error = ret_status;
	return (ret_status);
}

void	ft_child_process(t_data *data, t_block *block, int *fd)
{
	/*if (ft_is_builtin(block) == 2)	//command that doesn't work under fork
	{
		if (fd[0] != 0)
			close(fd[0]);
		if (fd[1] != 1)
			close(fd[1]);
		return ;
	}*/
	ft_redir(block, fd);
	if (fd[0] != STDIN_FILENO)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit_error(ERROR_DUP, NULL, data);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit_error(ERROR_DUP, NULL, data);	//TODO check if any fd need to be closed
	}
	ft_exec_under_fork(block, data);
}

int	*ft_fork(t_data *data, t_block *block, size_t childs, int **fds)
{
	int		*pid;
	size_t	i;
	int		child_fd[2];

	pid = malloc(sizeof(int) * (childs));
	if (!pid)
		return (NULL);		//TODO exit
	i = 0;
	while (i < childs)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (NULL);		//TODO free all and kill all childs
		if (pid[i] == 0)
		{
			ft_get_fd(fds, i, child_fd, childs - 1);
			ft_child_process(data, block, child_fd);
			free(pid);
			exit_child(data, fds, child_fd);
		}
		block = block->next;
		i++;
	}
	return (pid);
}
