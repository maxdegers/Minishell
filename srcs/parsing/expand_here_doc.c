/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:16:31 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/14 12:07:27 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_do_expan_size(char *line, t_data *data,
	size_t *i, size_t *j)
{
	size_t	start;
	size_t	end;
	char	*tmp;

	if (line[*i + 1] == '?')
	{
		tmp = ft_do_count(data, ft_itoa(g_error), 0, NULL);
		ft_add_to_str(data->error_cmd, j, tmp);
		*i += 1;
	}
	else if (ft_iscaracter_env(line[*i + 1]) == 1
		|| line[*i + 1] != '\0')
	{
		*i += 1;
		start = *i;
		while (line[*i] && ft_iscaracter_env(line[*i]) == 1)
			*i += 1;
		end = *i;
		tmp = ft_strdup_size(&line[start], end - start);
		tmp = ft_do_count(data, ft_envfind_data(data->env, tmp), 1, tmp);
		ft_add_to_str(data->error_cmd, j, tmp);
		*i -= 1;
	}
}

char	*do_expand_herdoc(t_data *data, char *line, size_t size)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(char), (size + 1));
	if (!new)
		exit_error(ERROR_MALLOC, NULL, data);
	data->error_cmd = new;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
			heredoc_do_expan_size(line, data, &i, &j);
		else
			new[j++] = line[i];
		i++;
	}
	free(line);
	return (new);
}

char	*ft_expand_heredoc(t_data *data, char *line)
{
	char	*res;
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			heredoc_calc_expan_size(line, data, &size, &i);
		}
		else
			size++;
		i++;
	}
	res = do_expand_herdoc(data, line, size);
	return (res);
}

int	here_doc_get_line(t_data *data, t_redir *redir, char *line)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		exit_error(ERROR_MALLOC, NULL, data);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("minishell: warning: here-document \
delimited by end-of-file (wanted `%s')\n", redir->file);
			break ;
		}
		if (ft_strcmp(line, redir->file) == 0)
			break ;
		res = join_lines(res, line, data);
	}
	free(line);
	res = ft_expand_heredoc(data, res);
	ft_heredoc_pipe(data, redir, res);
	if (!redir->file)
		exit_error(ERROR_MALLOC, NULL, data);
	return (free(res), 0);
}

int	ft_expand_here_doc(t_data *data)
{
	t_block	*block;
	t_redir	*redir;
	char	*line;

	block = data->block;
	line = NULL;
	while (block)
	{
		redir = block->redir;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				here_doc_get_line(data, redir, line);
			}
			redir = redir->next;
		}
		block = block->next;
	}
	return (0);
}
