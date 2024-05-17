/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:27:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/16 21:47:01 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_export_split(char *str, char *split)
{
	size_t	i;
	char	**tab;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == split[0])
			break ;
	}
	tab[0] = malloc(sizeof(char) * (i + 1));
	if (!tab[0])
		return (free(tab), NULL);
	ft_strlcpy(tab[0], str, i + 1);
	i += ft_strlen(split);
	if (str[i])
		tab[1] = ft_strdup(&str[i]);
	else
		tab[1] = NULL;
	if (!tab[1] && str[i])
		return (free(tab[0]), free(tab), NULL);
	tab[2] = NULL;
	return (tab);
}

int	determine_export_type(const char *arg)
{
	size_t	i;
	static char *s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";

	i = 0;
	while (arg[i] && ft_strchr(s, arg[i]))
		i++;
	if (i == 0)
		return (-1);
	if (!arg[i])
		return (1);
	if (arg[i] == '=')
		return (2);
	if (arg[i] == '+' && arg[i + 1] == '=')
		return (3);
	return (-1);
}

t_env	*ft_sort_env(t_env **env)
{
	t_env	*tmp;
	t_env	*head;
	char	*tmp_name;
	char	*tmp_value;

	head = *env;
	while (*env)
	{
		tmp = (*env)->next;
		while (tmp)
		{
			if (ft_strcmp((*env)->name, tmp->name) > 0)
			{
				tmp_name = (*env)->name;
				tmp_value = (*env)->value;
				(*env)->name = tmp->name;
				(*env)->value = tmp->value;
				tmp->name = tmp_name;
				tmp->value = tmp_value;
			}
			tmp = tmp->next;
		}
		*env = (*env)->next;
	}
	return (head);
}

t_env	*ft_dup_env(t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	new = NULL;
	while (env)
	{
		tmp = ft_envnew(env->name, env->value);
		if (!tmp)
			return (ft_envclear(&new), NULL);
		ft_envadd_back(&new, tmp);
		env = env->next;
	}
	return (new);
}

void	ft_put_env_exp(t_data *data)
{
	t_env	*dup;
	t_env	*tmp;

	dup = ft_dup_env(data->env);
	if (!dup)
		exit_error(ERROR_MALLOC, NULL, data);
	dup = ft_sort_env(&dup);
	tmp = dup;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "_") != 0)
		{
			if (tmp->show)
				ft_printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			else
				ft_printf("declare -x %s\n", tmp->name);
		}
		tmp = tmp->next;
	}
	ft_envclear(&dup);
}