/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:41:54 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/21 11:19:46 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_tab(t_env *env)
{
	char	**tab;
	size_t	i;

	i = 0;
	tab = malloc((sizeof(char *)) * (ft_envsize(env) + 1));
	if (!tab)
		return (NULL);
	while (env)
	{
		if (!env->show)
		{
			env = env->next;
			continue ;
		}
		tab[i] = ft_strjoin(env->name, "=");
		if (!tab[i])
			return (ft_free_tab(tab), NULL);
		tab[i] = ft_strjoin_free(tab[i], env->value, 1);
		if (!tab[i])
			return (ft_free_tab(tab), NULL);
		env = env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_envfind_data(t_env *env, char *name)
{
	if (name == NULL)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->name, name) && env->show)
			return (env->value);
		env = env->next;
	}
	return ("");
}

void	ft_create_env(t_data *data)
{
	t_env	*tmp;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit_error(ERROR_MALLOC, NULL, data);
	tmp = ft_envnew("PWD", pwd);
	if (!tmp)
	{
		free(pwd);
		exit_error(ERROR_MALLOC, NULL, data);
	}
	free(pwd);
	ft_envadd_back(&data->env, tmp);
	tmp = ft_envnew("SHLVL", "1");
	if (!tmp)
		exit_error(ERROR_MALLOC, NULL, data);
	ft_envadd_back(&data->env, tmp);
}

void	ft_check_env(t_data *data)
{
	t_env	*tmp;

	tmp = ft_envfind(data->env, "SHLVL");
	if (tmp == NULL)
	{
		tmp = ft_envnew("SHLVL", "1");
		if (!tmp)
			exit_error(ERROR_MALLOC, NULL, data);
		ft_envadd_back(&data->env, tmp);
	}
}

t_env	*ft_envfind_again(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}
