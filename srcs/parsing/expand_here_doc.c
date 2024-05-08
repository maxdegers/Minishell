/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:16:31 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/08 14:23:57 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_lines(char *s1, char *s2, t_data *data)
{
	char	*res;

	if (ft_strcmp(s1, "") == 0)
	{
		res = ft_strdup(s2);
		if (!res)
			exit_error(ERROR_MALLOC, NULL, data);
	}
	else
	{
		s1 = ft_strjoin_free(s1, "\n", 1);
		if (!s1)
			exit_error(ERROR_MALLOC, NULL, data);
		res = ft_strjoin_free(s1, s2, 2);
		if (!res)
			exit_error(ERROR_MALLOC, NULL, data);
	}
	if (!res)
		exit_error(ERROR_MALLOC, NULL, data);
	return (free(s1), res);
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
			return (free(res), free(line), 1);
		}
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		res = join_lines(res, line, data);
	}
	redir->file = ft_strdup(res);
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
				if (here_doc_get_line(data, redir, line) == 1)
					return (1);
			}
			redir = redir->next;
		}
		block = block->next;
	}
	return (0);
}
