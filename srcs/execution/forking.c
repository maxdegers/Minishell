/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:46:25 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/14 19:38:39 by mpitot           ###   ########.fr       */
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
		waitpid(pid[i], &ret_status, 0);
		if (WIFEXITED(ret_status))
			g_error = WEXITSTATUS(ret_status);
	}
	return (ret_status);
}

void	ft_child_process(t_data *data, t_block *block, int *fd)
{
	char	*redir_ret;

	redir_ret = ft_redir(block, fd);
	if (redir_ret)
	{
		if (errno == ENOENT)
			ft_printf_fd(2, "minishell: %s: No such file or directory\n", redir_ret);
		else if (errno == EACCES)
			ft_printf_fd(2, "minishell: %s: Permission denied\n", redir_ret);
		return ;
	}
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
