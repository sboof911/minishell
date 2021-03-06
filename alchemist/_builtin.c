/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:52:23 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/22 15:30:17 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *command)
{
	if (!command)
		return (0);
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
		ft_pwd(cmd);
	else if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
		ft_echo(cmd, 1);
	else if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
		ft_cd(cmd, env);
	else if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
		print(env);
	else if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
		ft_export(cmd, env);
	else if (!ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])))
		ft_unset(cmd, env);
	else if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
		ft_exit(cmd);
	return (1);
}
