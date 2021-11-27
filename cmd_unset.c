/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:52:01 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/11/27 17:52:04 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_key(char *argv, t_env *envs)
{
	t_env *curr;
	t_env *next;

	curr = envs;
	while (curr->next)
	{
		if (is_exist_key(argv, curr->next))
		{
			next = curr->next;
			curr->next = next->next;
			free((t_env *)next->key);
			free((t_env *)next->value);
			free(next);
			return ;
		}
		curr = curr->next;
	}
}

void			ft_unset(char **argv, t_env *envs)
{
	argv++;
	while (*argv)
	{
		delete_key(*argv, envs);
		argv++;
	}
}
