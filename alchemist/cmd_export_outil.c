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

char		*ft_sdtrjoin(const char *s1, const char *s2)
{
	char	*str;
	int		len1;
	int		len2;

	if (s1 && s2)
	{
		len1 = strlen(s1);
		len2 = strlen(s2);
		str = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
		if (!str)
			return (0);
		strlcpy(str, s1, len1 + 1);
		strlcat(str, s2, len1 + len2 + 1);
		return (str);
	}
	return (0);
}

int			ft_lstsize(t_env *lst)
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

void		print_arr(char **arr)
{
	int		index;

	index = 0;
	while (arr[index])
		ft_putendl_fd(arr[index++], 1);
}

void		free_arr(char **arr)
{
	int		index;

	if (!arr)
		return ;
	index = -1;
	while (arr[++index])
		free(arr[index]);
	free(arr);
}

int			is_valid_env(char *arg)
{
	int i = -1;
 
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

int			is_exist_key(char *key, t_env *envs)
{
	int		len;
	int		len_find = 0;
	int		len_exist = 0;

	// printf("key: %s\n", key);
	// printf("envs->key: %s\n", envs->key);
	len_find = ft_strlen(key);
	len_exist = ft_strlen((envs->key));
		// printf("key: %s\n", key);

	len = (len_find > len_exist) ? len_find : len_exist;
	if (ft_strncmp(key, envs->key, len) == 0)
		return (1);
	return (0);
}

void	    ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env *curr;

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

t_env	    *ft_lstnew(t_env *content)
{
	t_env	*new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	new->key = content->key;
	new->value = content->value;
	new->next = NULL;
	return (new);
}

char		*ft_ssubstr(char const *s, unsigned int start, size_t len)
{
	unsigned int	idx;
	char			*modified_s;

	if (!s || !(modified_s = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	idx = 0;
	while (start < ft_strlen((char *)s) && s[start + idx] && idx < len)
	{
		modified_s[idx] = s[start + idx];
		idx++;
	}
	modified_s[idx] = '\0';
	return (modified_s);
}

