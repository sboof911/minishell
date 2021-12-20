/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:58:26 by amaach            #+#    #+#             */
/*   Updated: 2021/12/20 10:34:54 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*temp;
	size_t			j;
	unsigned int	start1;

	start1 = start;
	if (!s)
		return (0);
	j = 0;
	if (start > (unsigned int)ft_strlen((char *)s))
		len = 0;
	temp = (char *)malloc(sizeof(char) * len + 1);
	while (start < start1 + (unsigned int)len && s[start])
	{
		temp[j] = s[start];
		start++;
		j++;
	}
	temp[j] = '\0';
	return (temp);
}
