/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:50:55 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/11/27 17:50:59 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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



	path = find_path(argv[0], envs);
	printf("path = %s\n", path);
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
	//g_exit_value = status / 256;*/
}

void 	exec_cmd(t_sashell *sashell, t_env *env)
{
	char **cmd;
	int ret;

	cmd = sashell->tokens;
	sashell->g_exit_value = 0;

	if (cmd && is_builtin(cmd[0]))
		ret = exec_builtin(cmd, env);
	else if (cmd)
		exec_others(cmd, env,  convert_env_to_arr(env));


	//if (ret == -1)
	//	perror("Error: exec cmd");
	/*
	if (has_pipe(line))
		exec_pipe(line, envs);
	else if (has_redir(line))
		exec_redir(line, envs);
	else if (!exec_dollar(line) && !exec_builtin(line, envs))
		exec_others(line, envs);	
	*/	
}

void	 minishell(t_sashell *sashell, t_env *env)
{


	// fuction to handle error on the sashell structure

	// go ahead and execute the shitty  commands
	exec_cmd(sashell, env);
}

int		main(int argc, char **argv, char **envp)
{
	char		*line;
	t_sashell	*sashell;
	t_env		*env;
	char		cwd[PATH_MAX];

	env = split_env(env, envp);
	while (1)
	{

		getcwd(cwd, PATH_MAX);
		printf("\e[48;5;098m~%s", cwd);
		line = readline("\e[48;5;098m $> \033[0m");
		if ( strcmp(line ,"") == 0 || !line)
			continue;
		else 
			{
				add_history(line);
				sashell = parse_function(sashell, env, line);
				if (sashell)
				{
					//print_arr(sashell->tokens);

					//printing data
					/*
					printf("\n\033[1;33m=============================|     Tokens    |========================================\033[0m\n");
					print_sashell(sashell);
					printf("\n\033[1;33m=============================| End of Tokens |========================================\033[0m\n\n");
					*/
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
