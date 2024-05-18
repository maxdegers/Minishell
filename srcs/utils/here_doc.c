/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:34:16 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/18 20:51:06 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cal_expand_utils(size_t *i, size_t *size, char *line, t_data *data)
{
	size_t	start;
	size_t	end;
	char	*tmp;

	*i += 1;
	start = *i;
	while (line[*i] && ft_iscaracter_env(line[*i], 1) == 1)
		*i += 1;
	if (ft_isdigit(line[*i]) == 1)
		*i += 1;
	end = *i;
	tmp = ft_strdup_size(&line[start], end - start);
	*size += ft_count(data, ft_envfind_data(data->env, tmp), 1);
	free(tmp);
	*i -= 1;
}

void	ft_expand_utils(size_t *i, size_t *j, t_token *token, t_data *data)
{
	size_t	start;
	size_t	end;
	char	*tmp;

	*i += 1;
	start = *i;
	while (token->data[*i] && ft_iscaracter_env(token->data[*i], 1) == 1)
		*i += 1;
	if (ft_isdigit(token->data[*i]) == 1)
		*i += 1;
	end = *i;
	tmp = ft_strdup_size(&token->data[start], end - start);
	tmp = ft_do_count(data, ft_envfind_data(data->env, tmp), 1, tmp);
	ft_add_to_str(token->new, j, tmp);
	*i -= 1;
}

void	ft_expand_heredoc_utils(size_t *i, size_t *j, char *line, t_data *data)
{
	size_t	start;
	size_t	end;
	char	*tmp;

	*i += 1;
	start = *i;
	while (line[*i] && ft_iscaracter_env(line[*i], 1) == 1)
		*i += 1;
	if (ft_isdigit(line[*i]) == 1)
		*i += 1;
	end = *i;
	tmp = ft_strdup_size(&line[start], end - start);
	tmp = ft_do_count(data, ft_envfind_data(data->env, tmp), 1, tmp);
	ft_add_to_str(data->error_cmd, j, tmp);
	*i -= 1;
}

int	ft_check_is_incote_heredoc(char *line)
{
	size_t	i;
	int		s_quote;
	int		d_quote;

	s_quote = -1;
	d_quote = -1;
	i = 0;
	while (line[i] && i < (ft_strlen(line) - 1))
	{
		if (line[i] == S_QUOTE)
			s_quote *= -1;
		if (line[i] == D_QUOTE)
			d_quote *= -1;
		i++;
	}
	if (s_quote == 1 || d_quote == 1)
		return (1);
	else
		return (0);
}
