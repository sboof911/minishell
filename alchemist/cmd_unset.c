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

#include "../minishell.h"

static void	delete_key(char *argv, t_env *envs)
{
	t_env	*curr;
	t_env	*next;

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

void	ft_unset(char **argv, t_env *envs)
{
	argv++;
	while (*argv)
	{
		delete_key(*argv, envs);
		argv++;
	}
	g_.exit_value = 0;
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_length;
	size_t	src_length;

	src_length = ft_strlen((char *)src);
	dest_length = ft_strlen(dst);
	j = dest_length;
	i = 0;
	if (dest_length < size - 1 && size > 0)
	{
		while (src[i] && dest_length + i < size - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = 0;
	}
	if (dest_length >= size)
		dest_length = size;
	return (dest_length + src_length);
}
