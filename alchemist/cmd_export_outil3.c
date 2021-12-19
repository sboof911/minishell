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
		if (ft_strlen(lst->value))
		{
			keytmp = ft_sdtrjoin((char *)lst->key, "=\"");
			valuetmp = ft_sdtrjoin((char *)lst->value, "\"");
		}
		else
		{
			keytmp = ft_sdtrjoin((char *)lst->key, "");
			valuetmp = ft_sdtrjoin((char *)lst->value, "");
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
