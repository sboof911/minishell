/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_outil2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 04:30:28 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/19 04:30:32 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_sdtrjoin(const char *s1, const char *s2)
{
	char	*str;
	int		len1;
	int		len2;

	if (s1 && s2)
	{
		len1 = strlen(s1);
		len2 = strlen(s2);
		str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (!str)
			return (0);
		strlcpy(str, s1, len1 + 1);
		strlcat(str, s2, len1 + len2 + 1);
		return (str);
	}
	return (0);
}

int	ft_lstsize(t_env *lst)
{
	int		index;
	t_env	*position;

	index = 0;
	position = lst;
	while (position != NULL)
	{
		position = position->next;
		index++;
	}
	return (index);
}

void	print_arr(char **arr)
{
	int		index;

	index = 0;
	while (arr[index])
		ft_putendl_fd(arr[index++], 1);
}

void	free_arr(char **arr)
{
	int		index;

	if (!arr)
		return ;
	index = -1;
	while (arr[++index])
		free(arr[index]);
	free(arr);
}
