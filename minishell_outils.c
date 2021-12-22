/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_outils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:54:22 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/22 15:57:12 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_sashell(t_sashell *sashell)
{
	t_sashell	*tmp;
	int			i;

	i = 0;
	while (sashell)
	{
		tmp = sashell->next;
		ft_free(sashell->tokens, 1024);
		ft_free(sashell->red, 1024);
		free(sashell);
		sashell = tmp;
	}
}

int	ft_token_count(t_token *token, t_sashell *sashell)
{
	while (sashell)
	{
		token->token_count++;
		sashell = sashell->next;
	}
	return (token->token_count);
}

int	exec_cmd(t_sashell *sashell, char **cmd, t_env *env, int i)
{
	t_redir	redir;

	redir.index_in = 0;
	redir.index_out = 0;
	if (sashell->red)
		if (exec_redirection(sashell, &redir))
			return (1);
	if (cmd && is_builtin(cmd[0]) && cmd[0][0])			// I did some changes here
	{
		if (exec_builtin(cmd, env) < 0)
			return (1);
	}
	else if (cmd && i > 1 && cmd[0][0])			// I did some changes here
		exec_others(cmd, env, g_.envp);
	else if (cmd && i == 1 && cmd[0][0])			// I did some changes here
		g_.exit_value = execo_others(cmd, env, g_.envp);
	else
	{
		ft_putstr("minishell: command not found: ");
		g_.exit_value = 127;
	}
	if (redir.index_in || redir.index_out)
		reset_redirection(&redir.in, &redir.out, &redir.fd);
	return (g_.exit_value);
}

void	minishell(t_sashell *sashell, t_env *env)
{
	char	**cmd;
	int		index;
	t_token	token;

	index = 0;
	token.token_count = 0;
	cmd = sashell->tokens;
	ft_token_count(&token, sashell);
	if (token.token_count > 1)
		g_.exit_value = exec_pipe(env, sashell, token.token_count);
	else if (cmd[0])
		exec_cmd(sashell, cmd, env, 1);
	else if (sashell->red[0])
	{
		if (sashell->red[0][4] == 't' && sashell->red[0][1 == '<'])
		{
			cmd[0] = ft_strdup("cat");
			cmd[1] = NULL;
			sashell->tokens[0] = cmd[0];
			exec_cmd(sashell, cmd, env, 1);
			g_.exit_value = 0;
		}
	}
}
