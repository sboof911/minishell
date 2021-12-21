/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_others_outils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:02:56 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/19 17:02:58 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error(char *str)
{
	ft_puterror_fd(str, ": command not found", 2);
	exit(127);
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
}

int	ft_puterror_fd(char *s1, char *s2, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putendl_fd(s2, fd);
	return (127);
}

int	is_exist_keyy(char *key, t_env *envs)
{
	int		len;
	int		len_find;
	int		len_exist;

	len_find = ft_strlen(key);
	len_exist = ft_strlen((char *)(envs->key));
	if (len_find > len_exist)
		len = len_find;
	else
		len = len_exist;
	if (ft_strncmp(key, envs->key, len) == 0)
		return (1);
	return (0);
}
