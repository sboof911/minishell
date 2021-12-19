/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:52:59 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/11/27 17:53:02 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	oldpwd = ft_sstrjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return (SUCCESS);
}

static int	go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", STDERR);
		if (!env_path)
			return (ERROR);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
		if (!env_path)
			return (ERROR);
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

char	*find_value(char *key, t_env *envs)
{
	while (envs)
	{
		if (is_exist_key(key, envs))
			return (envs->value);
		envs = envs->next;
	}
	return ("");
}

void	ft_cd(char **argv, t_env *envs)
{
	char	*path;

	path = 0;
	if (argv[1] == NULL || ((argv[1] != NULL) && \
		(ft_strlen(argv[1]) == 1) && (argv[1][0] == '~')))
	{
		path = find_value("HOME", envs);
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
			g_exit_value = 127;
		return ;
	}
	else if (*argv[1] == '$')
	{
		path = find_value(argv[1] + 1, envs);
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
			g_exit_value = 127;
		return ;
	}
	if (chdir(argv[1]) == -1)
		ft_putendl_fd(strerror(errno), 2);
}
