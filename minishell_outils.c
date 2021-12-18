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
				return (NULL);
			env = env->next;
		}
		i++;
	}
	env->next = NULL;
	env = tmp;
	return (env);
}

void			free_sashell(t_sashell *sashell)
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

void 			print_sashell(t_sashell *sashell)
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
			printf("pipe[%d]...tokens[%d] = |%s\n", compt, i, sashell->tokens[i]);
		i = -1;
		while (sashell->red[++i])
			printf("pipe[%d]...red[%d] = |%s\n", compt, i, sashell->red[i]);
		sashell = sashell->next;
		compt++;
	}
	printf("*********************************\n");
	sashell = tmp;
}