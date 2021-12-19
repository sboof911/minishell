/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_outil3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 04:55:33 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/19 04:55:35 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_key_value(t_env *lst, char **keytmp, char **valuetmp)
{
	if (ft_strlen(lst->value))
	{
		*keytmp = ft_sdtrjoin((char *)lst->key, "=\"");
		*valuetmp = ft_sdtrjoin((char *)lst->value, "\"");
	}
	else
	{
		*keytmp = ft_sdtrjoin((char *)lst->key, "");
		*valuetmp = ft_sdtrjoin((char *)lst->value, "");
	}
}

char	**convert_env_to_arr(t_env *lst)
{
	int		idx;
	int		count;
	char	**arr;
	char	*keytmp;
	char	*valuetmp;

	count = ft_lstsize(lst);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!(arr))
		return (NULL);
	idx = 0;
	while (lst)
	{
		assign_key_value(lst, &keytmp, &valuetmp);
		arr[idx] = ft_sdtrjoin(keytmp, valuetmp);
		free(keytmp);
		free(valuetmp);
		lst = lst->next;
		idx++;
	}
	arr[idx] = NULL;
	return (arr);
}

void	sort_double_arr(char **arr)
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

void	add_declare_for_export(char **arr)
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

int	error_display(char **cmd)
{
	ft_putstr_fd("export: `", 1);
	ft_putstr_fd(*cmd, 1);
	ft_putendl_fd("': not a valid identifier", 1);
	g_exit_value = 127;
	return (1);
}
