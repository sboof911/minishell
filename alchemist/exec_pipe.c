/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 20:45:41 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/19 20:45:44 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_child(t_sashell *sashell, t_redir *redir, int i)
{
	if (sashell->red)
		if (pipe_redirection(sashell, redir))
			return (1);
	if (i != 0)
	{
		dup2(redir->tmp_fd, 0);
		close(redir->tmp_fd);
	}
	return (0);
}

int	process(t_redir *redir, t_sashell *sashell, int *pfd, int i)
{
	if (pipe_child(sashell, redir, i))
		return (1);
	close(pfd[0]);
	if (i != redir->count - 1)
		dup2(pfd[1], 1);
	close(pfd[1]);
	return (0);
}

int	pipe_process(t_redir *redir, t_env *envs, t_sashell *sashell, pid_t *pid)
{
	int	pfd[2];
	int	i;

	i = -1;
	while (++i < redir->count)
	{
		if (pipe(pfd) == -1)
			return (1 && (printf("pipe failed\n")));
		pid[i] = fork();
		if ((i < redir->count) && (pid[i]) < 0)
			return (1 && (printf("fork failed\n")));
		if (pid[i] == 0)
		{
			process(redir, sashell, pfd, i);
			exec_cmd(sashell, sashell->tokens, envs, 2);
			exit(EXIT_FAILURE);
		}
		if (redir->tmp_fd != 0)
			close(redir->tmp_fd);
		sashell = sashell->next;
		redir->tmp_fd = pfd[0];
		close(pfd[1]);
	}
	close(pfd[0]);
	return (0);
}

void	init_redir(t_redir *redir)
{
	redir->index_in = 0;
	redir->index_out = 0;
	redir->in = 0;
	redir->out = 0;
	redir->fd = 0;
	redir->tmp_fd = 0;
}

int	exec_pipe(t_env *envs, t_sashell *sashell, int count)
{
	int			status;
	pid_t		*pid;
	t_redir		redir;
	int			i;

	i = 0;
	pid = (pid_t *)malloc(sizeof(pid_t) * count);
	init_redir(&redir);
	redir.count = count;
	if (pipe_process(&redir, envs, sashell, pid))
		return (1);
	i = 0;
	while (i < count)
		waitpid(pid[i++], &status, 0);
	free(pid);
	return (g_exit_value = status);
}
