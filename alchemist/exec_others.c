/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:51:08 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/19 16:51:10 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_valuee(char *key, t_env *envs)
{
	while (envs)
	{
		if (is_exist_keyy(key, envs))
			return (envs->value);
		envs = envs->next;
	}
	return ("");
}

char	*find_path(char *argv, t_env *envs)
{
	int			idx;
	char		*temp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	temp = find_valuee("PATH", envs);
	if (!(temp))
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

int	exec_others(char **argv, t_env *envs, char **g_envp)
{
	char	*path;

	path = find_path(argv[0], envs);
	if (*argv[0] == '.' || *argv[0] == '/')
		if (check_path(path, argv[0]))
			return (EXIT_FAILURE);
	if (!path)
	{
		ft_puterror_fd(argv[0], ": command not found", 2);
		return (EXIT_FAILURE);
	}
	if (execve(path, argv, g_envp) == -1)
		exit(ft_puterror_fd(argv[0], ": command not found", 2));
	free(path);
	exit(EXIT_SUCCESS);
}

int	check_path(char *path, char *argv)
{
	int	count;

	count = ft_strlen(path);
	if (ft_strncmp(path, argv, count))
	{
		ft_puterror_fd(argv, ": no such file or directory", 2);
		return (1);
	}
	return (0);
}

int	execo_others(char **argv, t_env *envs, char **g_envp)
{
	int		status;
	char	*path;
	pid_t	child;

	path = find_path(argv[0], envs);
	if (*argv[0] == '.' || *argv[0] == '/')
		if (check_path(path, argv[0]))
			return (EXIT_FAILURE);
	if (!path)
	{
		ft_puterror_fd(argv[0], ": command not found", 2);
		return (g_.exit_value = EXIT_FAILURE);
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
	return (g_.exit_value = status % 256);
}
