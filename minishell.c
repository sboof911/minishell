/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:50:55 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/20 10:21:34 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	ret;
	t_redir redir;

	redir.index_in = 0;
	redir.index_out = 0;
	ret = 0;
	if (sashell->red)
		if (exec_redirection(sashell, &redir))
			return (1);
	if (cmd && is_builtin(cmd[0]))
		exec_builtin(cmd, env);
	else if (cmd && i > 1)
		ret = exec_others(cmd, env, g_envp);
	else if (cmd && i == 1)
		ret = execo_others(cmd, env, g_envp);
	else
	{
		ft_putstr("minishell: command not found: ");
		ret = 127;
	}
	if (redir.index_in || redir.index_out)
		reset_redirection(&redir.in, &redir.out, &redir.fd);
	return (ret);
}

void	minishell(t_sashell *sashell, t_env *env, char *str)
{
	char	**cmd;
	int		index;
	t_token	token;

	index = 0;
	token.token_count = 0;
	cmd = sashell->tokens;
	sashell->g_exit_value = 0;
	ft_token_count(&token, sashell);
	if (token.token_count > 1)
		g_exit_value = exec_pipe(env, sashell, token.token_count);
	else if (cmd)
		g_exit_value = exec_cmd(sashell, cmd, env, 1);
	//free_arr(cmd);
}

int		find_shlvl(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	while (env)
	{
		if (ft_strncmp(env->key, "SHLVL", 5) == 0)
		{
			i = ft_atoi(env->value);
			env = tmp;
			return (i);
		}
		env = env->next;
	}
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_sashell	*sashell;
	t_env		*env;
	char		cwd[PATH_MAX];

	if (argc > 1)
	{
		printf("usage: ./minishell\n");
		return (1);
	}
	g_envp = envp;
	signal(SIGQUIT, &quit_handler);
	signal(SIGINT, &quit_handler);
	env = split_env(env, envp);
	while (1)
	{
		getcwd(cwd, PATH_MAX);
		printf("\e[48;5;098m~%s", cwd);

		line = readline("\e[48;5;098m $> \033[0m");
		if (line == NULL)
			break ;
		if (strcmp(line , "") == 0)
			continue;
		else
		{
			add_history(line);
			sashell = parse_function(sashell, env, line);
			if (sashell)
			{
				minishell(sashell, env, line);
				free_sashell(sashell);
			}
			// system("leaks minishell");
		}
	}
	free_env(env);
	return (0);
}
