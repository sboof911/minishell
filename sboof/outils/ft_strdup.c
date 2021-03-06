/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:18:48 by amaach            #+#    #+#             */
/*   Updated: 2021/10/20 12:29:37 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*temp;
	char	*s1;
	int		i;

	i = 0;
	s1 = (char *)s;
	if (!s1)
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	while (s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
