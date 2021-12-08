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

int		is_builtin(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (1);
	if (strcmp(command, "cd") == 0)
		return (1);
	if (strcmp(command, "pwd") == 0)
		return (1);
	if (strcmp(command, "env") == 0)
		return (1);
	if (strcmp(command, "export") == 0)
		return (1);
	if (strcmp(command, "unset") == 0)
		return (1);
	if (strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

char 	*ft_strl(char *s, size_t len)
{
	char *str;
	size_t i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	 	exec_builtin(char **cmd, t_env *env)
{
	if (!env || !cmd)
		return -1;
	if (!strcmp(cmd[0], "pwd"))
		g_exit_value = ft_pwd();
	else if (!strcmp(cmd[0], "echo"))
		g_exit_value = ft_echo(cmd, 1);
	else if (!strcmp(cmd[0], "cd"))
		ft_cd(cmd, env);
	else if (!strcmp(cmd[0], "env"))
		g_exit_value = print(env);
	else if (!strcmp(cmd[0], "export"))
		ft_export(cmd, env);
	else if (!strcmp(cmd[0], "unset"))
		ft_unset(cmd, env);
	else if (!strcmp(cmd[0], "exit"))
		ft_exit(cmd);
	return 1;
}
