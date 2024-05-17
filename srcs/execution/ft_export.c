/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:52 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/16 18:05:08 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_env_hidden(t_data *data, char *str)
{
	char	**tab;
	t_env	*new;

	tab = ft_export_split(str, "\0");
	if (!tab)
		return (1);
	if (ft_envfind(data->env, tab[0]))
		return (ft_free_tab(tab), 0);
	new = ft_envnew(tab[0], tab[1]);
	if (!new)
		return (ft_free_tab(tab), 1);
	ft_envadd_back(&data->env, new);
	return (ft_free_tab(tab), 1);
}

int	ft_add_env_shown(t_data *data, char *str)
{
	char	**tab;
	t_env	*new;
	t_env	*tmp;

	tab = ft_export_split(str, "=");
	if (!tab)
		return (1);
	tmp = ft_envfind(data->env, tab[0]);
	if (!tmp)
	{
		new = ft_envnew(tab[0], tab[1]);
		if (!new)
			return (ft_free_tab(tab), 1);
		ft_envadd_back(&data->env, new);
		return (ft_free_tab(tab), 0);
	}
	free(tmp->value);
	tmp->value = ft_strdup(tab[1]);
	if (!tmp->value)
		return (ft_free_tab(tab), 1);
	return (ft_free_tab(tab), 0);
}

int	ft_append_env(t_data *data, char *str)
{
	char	**tab;
	t_env	*new;
	t_env	*tmp;

	tab = ft_export_split(str, "+=");
	if (!tab)
		return (1);
	tmp = ft_envfind(data->env, tab[0]);
	if (!tmp)
	{
		new = ft_envnew(tab[0], tab[1]);
		if (!new)
			return (ft_free_tab(tab), 1);
		ft_envadd_back(&data->env, new);
		return (ft_free_tab(tab), 0);
	}
	tmp->value = ft_strjoin_free(tmp->value, tab[1], 1);
	if (!tmp->value)
		return (ft_free_tab(tab), 1);
	return (ft_free_tab(tab), 0);
}

int	ft_export(t_data *data, t_block *block)
{
	size_t	i;
	int		type;
	int		ret;

	if (!block->args[1])
		return (ft_put_env_exp(data), 0);
	i = 0;
	while (block->args[++i])
	{
		type = determine_export_type(block->args[i]);
		if (type == -1)
		{
			g_error = 1;
			ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n", block->args[i]);
			return (0);
		}
		if (type == 1)
			ret = ft_add_env_hidden(data, block->args[i]);
		if (type == 2)
			ret = ft_add_env_shown(data, block->args[i]);
		if (type == 3)
			ret = ft_append_env(data, block->args[i]);
		if (ret)
			return (1);
	}
	return (0);
}

void	ft_export_fork(t_data *data, t_block *block)
{
	size_t	i;

	if (!block->args[1])
		return (ft_put_env_exp(data));
	i = 0;
	while (block->args[++i])
	{
		if (determine_export_type(block->args[i]) == -1)
		{
			g_error = 1;
			ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n", block->args[i]);
			return ;
		}
	}
}