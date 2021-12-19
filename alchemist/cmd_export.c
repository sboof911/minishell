/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:54:00 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/11/27 17:54:05 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_value(t_env *env, t_env **envs)
{
	free((*envs)->value);
	(*envs)->value = env->value;
	free(env->key);
	free(env);
}

static void	assigne_value(char **argv, t_env *env)
{
	int	pos;

	pos = ft_strchr(*argv, '=') - *argv;
	if (pos < 1 || pos > (ft_strlen(*argv)))
	{
		env->key = ft_ssubstr(*argv, 0, ft_strlen(*argv));
		env->value = ft_strdup("");
	}
	else
	{
		env->key = ft_ssubstr(*argv, 0, pos);
		env->value = ft_ssubstr(*argv, pos + 1, ft_strlen(*argv) - pos - 1);
	}
}

static int	add_env_or_modify_value(char **argv, t_env **envs)
{
	t_env	*env;
	t_env	*curr;
	int		pos;

	pos = 0;
	env = (t_env *)malloc(sizeof(t_env));
	if (!(env))
		return (0);
	assigne_value(argv, env);
	curr = *envs;
	while (curr)
	{
		if (is_exist_key(env->key, curr))
		{
			update_value(env, &curr);
			return (0);
		}
		curr = curr->next;
	}
	if (curr == NULL)
		ft_lstadd_back(envs, ft_lstnew(env));
	return (0);
}

int	export_process(t_env *env)
{
	char	**tmp;

	tmp = convert_env_to_arr(env);
	sort_double_arr(tmp);
	add_declare_for_export(tmp);
	print_arr(tmp);
	free_arr(tmp);
	g_exit_value = 0;
	return (1);
}

void	ft_export(char **cmd, t_env *env)
{
	char	**tmp;
	int		index;

	if (cmd[1] == NULL)
		if (export_process(env))
			return ;
	cmd++;
	while (*cmd)
	{
		index = 0;
		if (!is_valid_env(*cmd))
		{
			if (!ft_isalpha(*cmd[0]))
			{
				if (error_display(cmd))
					return ;
			}
			else
				add_env_or_modify_value(cmd, &env);
		}
		else
			add_env_or_modify_value(cmd, &env);
		cmd++;
	}
}
