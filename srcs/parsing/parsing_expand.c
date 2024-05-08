/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:15:42 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/08 15:45:24 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_to_str(char *str, size_t *i, char *add)
{
	size_t	j;

	j = 0;
	while (add && add[j])
	{
		str[*i] = add[j];
		*i += 1;
		j++;
	}
	free(add);
}

char	*ft_do_count(t_data *data, char *s, int type, char *tmp2)
{
	char	*tmp;

	if (s == NULL && type == 0)
		exit_error(ERROR_MALLOC, NULL, data);
	if (type == 0)
		return (s);
	else
	{
		free(tmp2);
		if (s == NULL)
			exit_error(ERROR_MALLOC, NULL, data);
		tmp = ft_strdup(s);
		if (tmp == NULL)
			exit_error(ERROR_MALLOC, NULL, data);
		return (tmp);
	}
}

void	do_expan_size(t_token *token, t_data *data,
	size_t *i, size_t *j)
{
	size_t	start;
	size_t	end;
	char	*tmp;

	if (token->data[*i + 1] == '?')
	{
		tmp = ft_do_count(data, ft_itoa(g_error), 0, NULL);
		ft_add_to_str(token->new, j, tmp);
		*i += 1;
	}
	else if (ft_iscaracter_env(token->data[*i + 1]) == 1
		|| token->data[*i + 1] != '\0')
	{
		*i += 1;
		start = *i;
		while (token->data[*i] && ft_iscaracter_env(token->data[*i]) == 1)
			*i += 1;
		end = *i;
		tmp = ft_strdup_size(&token->data[start], end - start);
		tmp = ft_do_count(data, ft_envfind_data(data->env, tmp), 1, tmp);
		ft_add_to_str(token->new, j, tmp);
		*i -= 1;
	}
}

void	do_expan(t_data *data, t_token *token, size_t size, int quote)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(char), (size + 1));
	if (!new)
		exit_error(ERROR_MALLOC, NULL, data);
	token->new = new;
	while (token->data[i] != '\0')
	{
		if (token->data[i] == S_QUOTE)
			quote *= -1;
		if (token->data[i] == '$' && quote != 1)
			do_expan_size(token, data, &i, &j);
		else
			new[j++] = token->data[i];
		i++;
	}
	new[j] = '\0';
	free(token->data);
	token->data = new;
}

size_t	ft_count(t_data *data, char *s, int type)
{
	size_t	i;

	if (s == NULL && type == 0)
		exit_error(ERROR_MALLOC, NULL, data);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
