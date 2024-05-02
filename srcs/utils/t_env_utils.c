/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:41:54 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/01 13:41:36 by mpitot           ###   ########.fr       */
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

void	ft_envprint(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
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
