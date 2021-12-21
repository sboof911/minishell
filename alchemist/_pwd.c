/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:51:19 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/11/27 17:51:23 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **cmd)
{
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 1)
	{
		ft_putstr("pwd: too many arguments\n");
		g_.exit_value = 1;
		return (1);
	}
	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		g_.exit_value = 0;
		return (SUCCESS);
	}
	else
	{
		g_.exit_value = 1;
		return (ERROR);
	}
}
