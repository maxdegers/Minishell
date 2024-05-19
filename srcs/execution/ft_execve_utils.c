/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:10:58 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/18 21:10:58 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_path_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		g_error = 126;
		return (1);
	}
	return (0);
}

char	*ft_join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, cmd);
	return (free(tmp), res);
}

void	ft_print_error_path(t_block *block)
{
	if (g_error == 127 && block->cmd[0] == '.' && block->cmd[1] == '/')
		ft_printf_fd(2, "%s: No such file or directory\n", block->cmd);
	else if (g_error == 127 && block->cmd[0] == '/')
		ft_printf_fd(2, "minishell: %s: No such file or directory\n",
			block->cmd);
	else if (g_error == 127 || !block->cmd[0])
		ft_printf_fd(2, "%s: command not found\n", block->cmd);
	else if (g_error == 126 && (errno == ENOTDIR || errno == EACCES))
		ft_printf_fd(2, "%s: Permission denied\n", block->cmd);
	else if (g_error == 126)
		ft_printf_fd(2, "minishell: %s: Is a directory\n", block->cmd);
}
