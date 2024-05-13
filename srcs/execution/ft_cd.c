/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:30 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/13 15:11:56 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(t_data *data, const char *path)
{
	t_env	*tmp;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	tmp = ft_envfind(data->env, "PWD");
	if (!tmp)
	{
		ft_envadd_back(&data->env, ft_envnew("PWD", pwd));
		tmp = ft_envfind(data->env, "PWD");
	}
	free(tmp->value);
	tmp->value = ft_strdup(pwd);
	tmp = ft_envfind(data->env, "OLDPWD");
	if (!tmp)
	{
		ft_envadd_back(&data->env, ft_envnew("OLDPWD", (char *) path));
		tmp = ft_envfind(data->env, "OLDPWD");
	}
	free(tmp->value);
	tmp->value = ft_strdup(path);
	free(pwd);
}

void	ft_cd(t_block *block, t_data *data)
{
	t_block	*tmp;
	t_env	*env;
	char	*path;

	tmp = block;
	env = ft_envfind(data->env, "HOME");
	if (!tmp->args[1])
	{
		if (!env)
		{
			ft_printf("minishell: cd: HOME not set\n");
			g_error = 1;
			return ;
		}
        path = env->value;
	}
	else
        path = tmp->args[1];
	if (chdir(path) == -1)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
		g_error = 1;
	}
	update_env(data, path);
}
