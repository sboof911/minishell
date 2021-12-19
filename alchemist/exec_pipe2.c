/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:32:56 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/19 22:32:58 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_redire_in(t_redir *redir, char *file_name)
{
	redir->fd = open(file_name, O_RDONLY);
	if ((redir->fd) < 0)
	{
		printf("no such file or directory: %s\n", file_name);
		g_exit_value = 1;
		close(redir->fd);
		dup2(redir->in, 0);
		close(redir->in);
		free(file_name);
		return (1);
	}
	if ((dup2(redir->fd, redir->tmp_fd) < 0))
	{
		ft_putstr("minishell: command not found: ");
		return (1);
	}
	return (0);
}

int	pipe_redire_out(t_redir *redir, char *file_name)
{
	(redir->fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600));
	if ((redir->fd) < 0)
	{
		printf("no such file or directory: %s\n", file_name);
		g_exit_value = 1;
		close(redir->fd);
		dup2(redir->out, 1);
		close(redir->out);
		free(file_name);
		return (1);
	}
	if ((dup2(redir->fd, 1) < 0))
	{
		ft_putstr("minishell: command not found: ");
		g_exit_value = 1;
		close(redir->fd);
		dup2(redir->out, 1);
		close(redir->out);
		free(file_name);
		return (1);
	}
	return (0);
}

int	pipe_redirection(t_sashell *sashell, t_redir *redir)
{
	int		p;
	char	*file_name;

	p = 0;
	redir->in = dup(0);
	redir->out = dup(1);
	while (sashell->red[p])
	{
		file_name = ft_strdup(sashell->red[p] + 3);
		if (sashell->red[p][1] == '<')
		{
			redir->index_in++;
			if (pipe_redire_in(redir, file_name))
				return (1);
		}
		else if (sashell->red[p][1] == '>')
		{
			redir->index_out++;
			if (pipe_redire_out(redir, file_name))
				return (1);
		}
		free(file_name);
		p++;
	}
	return (0);
}
