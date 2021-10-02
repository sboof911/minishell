/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:28:23 by amaach            #+#    #+#             */
/*   Updated: 2021/07/06 14:32:47 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	t;
	char	*temp;

	if (!s1)
		return (0);
	if (!s2)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	t = -1;
	if (!(temp = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (0);
	if (!temp)
		return (NULL);
	while (++t < i + j)
	{
		if (t < i)
			temp[t] = s1[t];
		else
			temp[t] = s2[t - i];
	}
	temp[t] = '\0';
    free (s1);
	return (temp);
}
