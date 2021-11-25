
#include "minishell.h"

t_env	*fill_env(t_env *env, char *envp)
{
	char	**help;

	help = ft_split(envp, '=');
	env->key = ft_strdup(help[0]);
	env->value = ft_strdup(help[1]);
	ft_free(help, 0);
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

void 	print_sashell(t_sashell *sashell)
{
	int i = 0;
	t_sashell	*tmp;
	int compt;

	tmp = sashell;
	compt = 1;
	while (sashell)
	{
		i = -1;
		printf("*********************************\n");
		while (sashell->tokens[++i])
			printf("pipe[%d]...tokens[%d] = %s\n", compt, i, sashell->tokens[i]);
		i = -1;
		while (sashell->red[++i])
			printf("pipe[%d]...red[%d] = %s\n", compt, i, sashell->red[i]);
		sashell = sashell->next;
		compt++;
	}
	printf("*********************************\n");
	sashell = tmp;
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
	// free(env);
}

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
	// free(sashell);
}

void 	exec_cmd(t_sashell *sashell, t_env *env)
{
	char **cmd;
	int ret;

	cmd = sashell->tokens;

	if (cmd && is_builtin(cmd[0]))
		ret = exec_builtin(cmd, env);

	//printf("ret = %d ", ret);
	if (ret == -1)
		perror("Error: exec cmd");


	// executable
	//if ()
	//	ret = 

}

void minishell(t_sashell *sashell, t_env *env)
{


	// fuction to handle error on the sashell structure

	// condition to check if it's a built-in 
	exec_cmd(sashell, env);


}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_sashell	*sashell;
	t_env		*env;

	env = split_env(env, envp);
	while (1)
	{
		line = readline("\033[0;34mSASHELL $> \033[0m");
		if ( strcmp(line ,"") == 0 || !line)
			continue;
		else 
			{
				add_history(line);
				sashell = parse_function(sashell, env, line);
				if (sashell)
				{
					//printing data
					printf("\n\033[1;33m=============================|     Tokens    |========================================\033[0m\n");
					print_sashell(sashell);
					printf("\n\033[1;33m=============================| End of Tokens |========================================\033[0m\n\n");
					
					// main-execution-process
					minishell(sashell, env);

					free_sashell(sashell);
				}
				//system("leaks minishell");
			}
	}
	free_env(env);
	return (0);
}
