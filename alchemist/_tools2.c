/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tools2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:12:27 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/19 17:12:29 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (*(s1 + i) && *(s1 + i) == *(s2 + i))
		i++;
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}

char	*ft_strcpy(char *dst, const char *src)
{
	int		i;

	if (!dst)
		return (NULL);
	if (!src)
		return (dst);
	i = -1;
	while (*(src + ++i))
		*(dst + i) = *(src + i);
	*(dst + i) = '\0';
	return (dst);
}

void	reset_redirection(int *in, int *out, int *fd)
{
	dup2(*in, 0);
	dup2(*out, 1);
	close(*fd);
	close(*out);
	close(*in);
}
