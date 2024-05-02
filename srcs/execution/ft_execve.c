/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/01 16:07:16 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(t_data *data, char *cmd)
{
	char	**path;
	char	*res;
	size_t	i;

	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 1)
			return (cmd);
		return (NULL);
	}
	path = get_path(data);
	if (!path)
		exit_error(ERROR_MALLOC, NULL, data);
	i = -1;
	res = NULL;
	while (path[++i])
	{
		res = ft_strjoin(path[i], "/");
		res = ft_strjoin_free(res, cmd, 1);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
	}
	return (NULL);
}

int	ft_execve(t_data *data, t_block *block, int *fd)
{
	char	**envp;
	int		pid;
	char	*path;

	envp = ft_env_to_tab(data->env);
	if (!envp)
		exit_error(ERROR_MALLOC, NULL, data);
	path = ft_get_path(data, block->cmd);
//	path = ft_strdup("/bin/ls");
	if (!path)
	{
		ft_printf_fd(1, "%s: command not found\n", block->cmd);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{	//CHILD
		dup2(fd[1], STDOUT_FILENO);
		if (execve(path, block->args, envp) == -1)
			exit(0);
	}
	else
	{	//PARENT
		wait(NULL);
		return (0);
	}
	ft_free_tab(envp);
	free(path);
	return (0);
}