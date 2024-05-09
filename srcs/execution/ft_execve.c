/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/02 16:36:05 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(t_data *data, char *cmd)
{
	char	**path;
	char	*res;
	char	*pwd;
	size_t	i;

	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		pwd = getcwd(NULL, 0);
		res = ft_strjoin_free(pwd, "/", 1);
		res = ft_strjoin_free(res, cmd, 1);
		if (access(res, F_OK | X_OK) == 0)
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

void	ft_execve(t_data *data, t_block *block)		//TODO refaire la fonction nette
{
	char	**envp;
	int		pid;
	char	*path;

	envp = ft_env_to_tab(data->env);
	if (!envp)
		exit_error(ERROR_MALLOC, NULL, data);
	path = ft_get_path(data, block->cmd);
	if (!path)
	{
		ft_printf_fd(1, "%s: command not found\n", block->cmd);
		return ;
	}
	if (execve(path, block->args, envp) == -1)
	{
		ft_free_tab(envp);
		free(path);
		exit_error(ERROR_EXEC, NULL, data);
	}
	return ;
}