#include "../minishell.h"

void	free_double_arr(char **arr)
{
	int		idx;

	if (!arr)
		return ;
	idx = -1;
	while (arr[++idx])
		free(arr[idx]);
	free(arr);
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

int		ft_puterror_fd(char *s1, char *s2, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putendl_fd(s2, fd);
	return (127);
}

int			is_exist_keyy(char *key, t_env *envs)
{
	int		len;
	int		len_find;
	int		len_exist;

	len_find = ft_strlen(key);
	len_exist = ft_strlen((char *)(envs->key));
	len = (len_find > len_exist) ? len_find : len_exist;
	if (ft_strncmp(key, envs->key, len) == 0) 
		return (1);
	return (0);
}

char		*find_valuee(char *key, t_env *envs)
{
	while (envs)
	{
		if (is_exist_keyy(key, envs))
			return (envs->value);
		envs = envs->next;
	}
	return ("");
}

char		*find_path(char *argv, t_env *envs)
{
	int			idx;
	char		*temp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	if (!(temp = find_valuee("PATH", envs)))
		return (NULL);
	paths = ft_split(temp, ':');
	idx = -1;
	while (paths[++idx])
	{
		temp = ft_sstrjoin("/", argv);
		new_path = ft_sstrjoin(paths[idx], temp);
		free(temp);
		if (stat(new_path, &s) == 0)
		{
			free_double_arr(paths);
			return (new_path);
		}
		free(new_path);
	}
	free_double_arr(paths);
	return (ft_strdup(argv));
}

void			exec_others(char **cmd, t_env *envs, char **g_envp)
{
	int		status;
	char	*path;
	char	**argv;
	pid_t	child;

	argv = cmd;


	//if (!strcmp(cmd[0], "clear"))
	//{
		//printf("\033c");
	//	return ;
	//}
	path = find_path(argv[0], envs);
	if (!path)
	{
		ft_puterror_fd(argv[0], ": command not found", 2);
		return ;
	}
	child = fork();
	if (child == 0)
	{
		if (execve(path, argv, g_envp) == -1)
			exit(ft_puterror_fd(argv[0], ": command not found", 2));
		exit(EXIT_SUCCESS);
	}
	wait(&status);
	free(path);
	//free_double_arr(argv);
	g_exit_value = status / 256;
}
