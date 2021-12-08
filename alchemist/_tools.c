/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tools.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:52:41 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/11/27 17:52:44 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_sstrjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	if (!(new = malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}


void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		ptr = NULL;
	}
	return (NULL);
}


void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int		print(t_env *head) {
    t_env *current_node = head;

   	while ( current_node != NULL)
	{
        printf("%s=%s\n", current_node->key, current_node->value);
        current_node = current_node->next;
    }
	return 1;
}

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	int		len;

	s = (char *)str;
	len = strlen(str);
	s += len;
	while (len >= 0)
	{
		if (*s == (char)c)
			return (s);
		s--;
		len--;
	}
	return (0);
}

