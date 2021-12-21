/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:50:55 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/21 18:05:35 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_shlvl(t_env *env)
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

void	main_process(char *line, t_sashell *sashell, t_env *env)
{
	add_history(line);
	sashell = parse_function(sashell, env, line);
	if (sashell)
	{
		g_.pid = 1;
		minishell(sashell, env);
		g_.pid = 0;
		free_sashell(sashell);
	}
}

int	init_shell(int argc, char **envp, t_env **env, char **argv)
{
	argv = NULL;
	if (argc > 1)
	{
		printf("usage: ./minishell\n");
		return (1);
	}
	g_.envp = envp;
	signal(SIGQUIT, &quit_handler);
	signal(SIGINT, &quit_handler);
	*env = split_env(*env, envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_sashell	*sashell;
	t_env		*env;

	sashell = NULL;
	if (init_shell(argc, envp, &env, argv))
		return (1);
	while (1)
	{
		line = readline("Sashell ?> ");
		if (!line)
			break ;
		if (strcmp(line, "") == 0)
			continue ;
		else
			main_process(line, sashell, env);
		system("leaks minishell");
	}
	free_env(env);
	return (0);
}
