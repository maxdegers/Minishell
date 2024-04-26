/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:22:35 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/26 12:09:40 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_to_str(char *str, size_t *i, char *add)
{
	size_t	j;

	j = 0;
	while (add[j])
	{
		str[*i] = add[j];
		*i += 1;
		j++;
	}
	free(add);
}

void	expansion2(t_token *token, size_t *i, size_t *j, t_data *data)
{
	char	c;
	size_t	start;
	char	*tmp;

	if (token->data[*i + 1] == '?')
	{
		tmp = ft_itoa(g_error);
		if (!tmp)
			exit_error(ERROR_MALLOC, "malloc error", data);
		ft_add_to_str(token->new, j, tmp);
		*i += 1;
	}
	else
	{
		start = *i + 1;
		while (token->data[*i]
			&& token->data[*i] != ' ' && token->data[*i] != '$')
			*i += 1;
		c = token->data[*i];
		token->data[*i] = '\0';
		tmp = ft_strdup(ft_envfind_data(data->env, &token->data[start]));
		token->data[*i] = c;
		ft_add_to_str(token->new, j, tmp);
	}
}

void	ft_param_expansion2(t_token *token, size_t size, t_data *data)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		exit_error(ERROR_MALLOC, "malloc error\n", data);
	i = 0;
	j = 0;
	token->new = new;
	while (token->data[i] != '\0' && j < size)
	{
		if (token->data[i] == '$' && token->data[i + 1] != '\0')
			expansion2(token, &i, &j, data);
		else
			new[j] = token->data[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(token->data);
	token->data = new;
}

void	expansion1(t_token *tmp, size_t *size, t_data *data, size_t *i)
{
	char	c;
	size_t	start;

	start = 0;
	if (tmp->data[*i + 1] == '?')
	{
		*size += strlen(ft_itoa(g_error));
		*i += 1;
	}
	else
	{
		start = *i + 1;
		*i += 1;
		while (tmp->data[*i] && tmp->data[*i] != ' ' && tmp->data[*i] != '$')
			*i += 1;
		c = tmp->data[*i];
		tmp->data[*i] = '\0';
		*size += ft_strlen(ft_envfind_data(data->env, &tmp->data[start]));
		tmp->data[*i] = c;
	}
}

void	ft_param_expansion(t_data *data)
{
	t_token	*tmp;
	size_t	i;
	size_t	size;

	tmp = data->token;
	while (tmp)
	{
		i = 0;
		size = 0;
		while (tmp->data[i])
		{
			if (tmp->data[i] == '$' && tmp->data[i + 1] != '\0')
				expansion1(tmp, &size, data, &i);
			else
				size++;
			i++;
		}
		printf("size = %zu\n", size);
		ft_param_expansion2(tmp, size, data);
		tmp = tmp->next;
	}
}
