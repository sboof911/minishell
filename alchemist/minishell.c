/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:10:34 by amaach            #+#    #+#             */
/*   Updated: 2021/07/09 20:10:05 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sboof/minishell.h"
#include <string.h>

t_env	*fill_env(t_env *env, char *envp)
{
	char	**help;

	help = ft_split(envp, '=');
	env->key = ft_strdup(help[0]);
	env->value = ft_strdup(help[1]);
	return (env);
}

t_env	*split_env(t_env *env, char **envp)
{
	t_env	*tmp;
	int		i;

	env = (t_env *)malloc(sizeof(t_env));
	i = 1;
	env = fill_env(env, envp[0]);
	tmp = env;
	env->next = (t_env *)malloc(sizeof(t_env));
		if (!env->next)
			return (NULL);
	env = env->next;
	while (envp[i])
	{
		env = fill_env(env, envp[i]);
		if (envp[i + 1])
		{
			env->next = (t_env *)malloc(sizeof(t_env));
			if (!env->next)
				return NULL;
			env = env->next;
		}
		i++;
	}
	env->next = NULL;
	env = tmp;
	return (env);
}

void print_sashell(t_sashell *sashell)
{
	int i = 0;

	while (sashell->tokens[i] != '\0')
	{
		if (i == 0)
			printf("command = %s\n", sashell->tokens[i++]);
		if (sashell->tokens[i] != '\0')
			printf("arg %s\n", sashell->tokens[i]);
		else
			break;
		i++;
	}
}



void exec_cmd(t_sashell *sashell)
{
	char **cmd;
	int ret;

	cmd = sashell->tokens;

	if (cmd && is_builtin(cmd[0]))
		ret = exec_builtin(cmd);


}

void minishell(t_sashell *sashell)
{
	// fuction to handle error on the sashell structure

	// condition to check if it's a built-in 
	exec_cmd(sashell);




}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**tab;
	t_sashell	*sashell;
	t_env		*env;

	while (1)
	{
		line = readline("SASHELL $");
		add_history(line);
		env = split_env(env, envp);
		sashell = parse_function(sashell, env, line);
	
		minishell(sashell);
		// tmp = sashell;
		// compt = 1;
		// while (sashell)
		// {
		// 	i = -1;
		// 	printf("*********************************\n");
		// 	while (sashell->tokens[++i])
		// 		printf("pipe[%d]...tokens[%d] = %s\n", compt, i, sashell->tokens[i]);
		// 	i = -1;
		// 	while (sashell->red[++i])
		// 		printf("pipe[%d]...red[%d] = %s\n", compt, i, sashell->red[i]);
		// sashell = sashell->next;
		// 	compt++;
		// }
		// printf("*********************************\n");
		// sashell = tmp;
	}
	return (0);
}
