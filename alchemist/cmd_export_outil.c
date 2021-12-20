/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_outil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:51:41 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/11/27 17:51:44 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_env(char *arg)
{
	int	i;

	i = -1;
	if (ft_isdigit(arg[0]) || arg[0] == '=')
		return (0);
	if (ft_strchr(arg, '='))
	{
		while (arg[++i])
			if (ft_isdigit(arg[i]))
				return (0);
		return (1);
	}
	return (0);
}

int	is_exist_key(char *key, t_env *envs)
{
	int		len;
	int		len_find;
	int		len_exist;

	len_find = 0;
	len_exist = 0;
	len_find = ft_strlen(key);
	len_exist = ft_strlen((envs->key));
	if (len_find > len_exist)
		len = len_find;
	else
		len = len_exist;
	if (ft_strncmp(key, envs->key, len) == 0)
		return (1);
	return (0);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*curr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}

t_env	*ft_lstnew(t_env *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!(new))
		return (NULL);
	new->key = content->key;
	new->value = content->value;
	new->next = NULL;
	return (new);
}

char	*ft_ssubstr(char const *s, unsigned int start, size_t len)
{
	unsigned int	idx;
	char			*modified_s;

	modified_s = malloc(sizeof(char) * (len + 1));
	if (!s || !(modified_s))
		return (NULL);
	idx = 0;
	while (start < (unsigned int)ft_strlen((char *)s) && s[start + \
	idx] && idx < len)
	{
		modified_s[idx] = s[start + idx];
		idx++;
	}
	modified_s[idx] = '\0';
	return (modified_s);
}
