/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:46:25 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/19 23:53:07 by mpitot           ###   ########.fr       */
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

static void	ft_error_open(char *str)
{
	if (errno == ENOENT)
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n", str);
		g_error = 1;
	}
	else if (errno == EACCES)
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", str);
		g_error = 1;
	}
	else if (errno == EISDIR)
	{
		ft_printf_fd(2, "minishell: %s: Is a directory\n", str);
		g_error = 126;
	}
}

static void	ft_child_process(t_data *data, t_block *block, int *fd)
{
	char	*redir_ret;

	redir_ret = ft_redir(block, fd);
	if (redir_ret)
		return (ft_error_open(redir_ret));
	if (fd[0] != STDIN_FILENO)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit_error(ERROR_DUP, NULL, data);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit_error(ERROR_DUP, NULL, data);
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
		return (ft_free_int_tab(fds), exit_error(1, NULL, data), NULL);
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
			ft_close_heredoc_pipe(data);
			exit_child(data, fds, child_fd);
		}
		block = block->next;
		i++;
	}
	return (pid);
}
