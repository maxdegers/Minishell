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
