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


char 			**convert_env_to_arr(t_env *lst) 
{
    int		idx;
	int		count;
	char	**arr;
	char	*keytmp;
	char	*valuetmp;

	count = ft_lstsize(lst);
	if (!(arr = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	idx = 0;
	while (lst)
	{
		if (ft_strlen(lst->value))
			{
				keytmp =   ft_sdtrjoin( (char *)lst->key, "=\"");
				valuetmp = ft_sdtrjoin( (char *)lst->value, "\"");
			}
		else
			{
				keytmp =   ft_sdtrjoin( (char *)lst->key, "");
				valuetmp = ft_sdtrjoin( (char *)lst->value, "");
			}

		arr[idx] = ft_sdtrjoin(keytmp, valuetmp);
		free(keytmp);
		free(valuetmp);
		lst = lst->next;
		idx++;
	}
	arr[idx] = NULL;
	return (arr);

}

void			sort_double_arr(char **arr)
{
	int		i;
	char	*temp;

	i = 0;
	while (arr[i + 1])
	{
		if (ft_strncmp(arr[i], arr[i + 1], 100) > 0)
		{
			temp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = temp;
			i = -1;
		}
		i++;
	}
}

void			add_declare_for_export(char **arr)
{
	int		index;
	char	*tmp;

	index = 0;
	while (arr[index])
	{
		tmp = ft_sdtrjoin("declare -x ", arr[index]);
		free(arr[index]);
		arr[index] = tmp;
		index++;
	}
}

static void		update_value(t_env *env, t_env **envs)
{
	//free(env->value); 
	free((*envs)->value);
	(*envs)->value = env->value;
	free(env->key);
	free(env);
}

static int		add_env_or_modify_value(char **argv, t_env **envs)
{
	t_env	*env;
	t_env	*curr;
	int		pos;

	pos = 0;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return 0;

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
	curr = *envs;
	while (curr)
	{
		if (is_exist_key(env->key, curr))
		{
			update_value(env, &curr);
			return 0;
		}
		curr = curr->next;
	}
	if (curr == NULL)
		ft_lstadd_back(envs, ft_lstnew(env));
	return 0;
}

void 			ft_export(char **cmd, t_env *env)
{
    char **tmp;
	int index = 0;

    if (cmd[1] == NULL)
    {
        tmp = convert_env_to_arr(env);
        sort_double_arr(tmp);
        add_declare_for_export(tmp);
		print_arr(tmp);
		free_arr(tmp);
		g_exit_value = 0;
        return;
    }
    cmd++;
	while (*cmd)
	{	
		index = 0;
		if (!is_valid_env(*cmd))
		{
			if (!ft_isalpha(*cmd[0]))
				{
					ft_putstr_fd("export: `", 1);
					ft_putstr_fd(*cmd, 1);
					ft_putendl_fd("': not a valid identifier", 1);
					g_exit_value = 127;
					return;
				}
			else 
				add_env_or_modify_value(cmd, &env);
		}
		else 
			add_env_or_modify_value(cmd, &env);
		cmd++;
	}
}