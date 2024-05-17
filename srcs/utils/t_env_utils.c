/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:41:54 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/14 14:01:45 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_env(t_env *env, char *name, char *value)
{
	t_env	*tmp;

	tmp = ft_envfind(env, name);
	if (!tmp)
		return (1);
	free(tmp->value);
	tmp->value = ft_strdup(value);
	if (!tmp->value)
		return (1);
	return (0);
}

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

char	*ft_envfind_data_size(t_env *env, char *name, size_t size)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, size) && env->show)
			return (env->value);
		env = env->next;
	}
	return ("");
}

// void	ft_envprint(t_env *env)
// {
// 	while (env)
// 	{
// 		ft_printf("%s=%s\n", env->name, env->value);
// 		env = env->next;
// 	}
// }
