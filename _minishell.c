
#include "minishell.h"

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

void 	exec_cmd(t_sashell *sashell, t_env *env)
{
	char **cmd;
	int ret;

	cmd = sashell->tokens;

	if (cmd && is_builtin(cmd[0]))
		ret = exec_builtin(cmd, env);



}

void minishell(t_sashell *sashell, t_env *env)
{


	// fuction to handle error on the sashell structure

	// condition to check if it's a built-in 
	exec_cmd(sashell, env);
	//print(env);




}


int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_sashell	*sashell;
	t_env		*env;

	while (1)
	{
		line = readline("SASHELL $> ");
		if ( strcmp(line ,"") == 0)
			continue;
		else 
			{
				add_history(line);
				env = split_env(env, envp);
				sashell = parse_function(sashell, env, line);
				// minishell(sashell, env);
				print_sashell(sashell);
			}
	}
	return (0);
}
