/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:52:23 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/11/27 17:52:26 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **cmd, t_env *env)
{
	if (!env || !cmd)
		return (-1);
	if (!ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])))
		g_.exit_value = ft_pwd();
	else if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
		g_.exit_value = ft_echo(cmd, 1);
	else if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
		ft_cd(cmd, env);
	else if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
		g_.exit_value = print(env);
	else if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
		ft_export(cmd, env);
	else if (!ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])))
		ft_unset(cmd, env);
	else if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
		ft_exit(cmd);
	return (1);
}
