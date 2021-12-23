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

int	to_path(t_env *envs)
{
	char	*path;

	path = find_value("HOME", envs);
	if (chdir(path) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		g_.exit_value = 1;
	}
	else
		g_.exit_value = 0;
	return (1);
}

void	to_env_path(t_env *envs, char *str)
{
	char	*path;

	path = find_value(str + 1, envs);
	if (chdir(path) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		g_.exit_value = 1;
	}
	else
		g_.exit_value = 0;
}

void	ft_cd(char **argv, t_env *envs)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	*cmd;

	cmd = ft_sstrjoin("OLPWD=", cwd);
	add_env_or_modify_value(&cmd, &envs);
	path = 0;
	if (argv[1] == NULL || ((argv[1] != NULL) && \
		(ft_strlen(argv[1]) == 1) && (argv[1][0] == '~')))
	{
		if (to_path(envs))
			return ;
	}
	else if (*argv[1] == '$')
	{
		to_env_path(envs, argv[1]);
		return ;
	}
	if (chdir(argv[1]) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		g_.exit_value = 1;
	}
	else
		g_.exit_value = 0;
}
