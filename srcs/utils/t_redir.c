/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:17:42 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/06 13:44:39 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_redir_new(char *data, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = ft_strdup(data);
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_redir_add_back(t_redir **redir, t_redir *new)
{
	t_redir	*tmp;

	if (!(*redir))
	{
		(*redir) = new;
		return ;
	}
	tmp = (*redir);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_add_redir(t_block *block, char *file, int type, t_data *data)
{
	t_redir	*new;

	new = ft_redir_new(file, type);
	if (!new)
		exit_error(ERROR_MALLOC, NULL, data);
	ft_redir_add_back(&block->redir, new);
}

void	ft_redir_print(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		ft_printf("file: %s\t", tmp->file);
		tmp = tmp->next;
	}
	tmp = redir;
	while (tmp)
	{
		ft_printf("type: %d\t", tmp->type);
		tmp = tmp->next;
	}
	ft_printf("\n");
}
