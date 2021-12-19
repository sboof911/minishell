/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:20:58 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/19 18:21:00 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_in(t_redir *redir, char *file_name)
{
	(redir->index_in)++;
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
	if ((dup2(redir->fd, 0) < 0))
	{
		ft_putstr("minishell: command not found: ");
		return (1);
	}
	return (0);
}

int	open_file(char *file_name, t_sashell *sashell, int p)
{
	if (sashell->red[p][0] == '2')
		return (open(file_name, O_WRONLY | O_APPEND \
		| O_CREAT, 0777));
	else
		return (open(file_name, O_WRONLY | O_TRUNC \
		| O_CREAT, 0777));
}

int	redir_ou(t_redir *redir, char *file_name, t_sashell *sashell, int p)
{
	(redir->index_out)++;
	redir->fd = open_file(file_name, sashell, p);
	if (redir->fd < 0)
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

int	redirection(t_sashell *sashell, t_redir *redir, char *file_name, int p)
{
	if (sashell->red[p][1] == '<')
	{
		if (redir_in(redir, file_name))
			return (1);
	}
	else if (sashell->red[p][1] == '>')
	{
		if (redir_ou(redir, file_name, sashell, p))
			return (1);
	}
	return (0);
}

int	exec_redirection(t_sashell *sashell, t_redir *redir)
{
	int		p;
	char	*file_name;

	p = 0;
	if (sashell->red)
	{
		redir->in = dup(0);
		redir->out = dup(1);
		p = 0;
		redir->index_in = 0;
		redir->index_out = 0;
		while (sashell->red[p])
		{
			file_name = ft_strdup(sashell->red[p] + 3);
			if (redirection(sashell, redir, file_name, p))
				return (1);
			free(file_name);
			p++;
		}
	}
	return (0);
}
