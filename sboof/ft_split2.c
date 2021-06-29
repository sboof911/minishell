/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:13:35 by amaach            #+#    #+#             */
/*   Updated: 2021/06/29 13:09:10 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count_words(char const *s, char c)
{
	int		i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]) || (i == 0 && s[i] != c))
			j++;
		i++;
	}
	return (j);
}

int		ft_lw(char const *s, char c, int i)
{
	size_t	j;

	j = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

void		*ft_free(char **s, int i)
{
	while (i--)
		free(s[i]);
	free(s);
	return (0);
}

char			**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!s)
		return (0);
	if (!(str = (char **)malloc(sizeof(char *) * ((ft_count_words(s, c) + 1)))))
		return (NULL);
	while (s[k] != '\0' && i < ft_count_words(s, c))
	{
		j = 0;
		while (s[k] == c)
			k++;
		if (!(str[i] = (char *)malloc(sizeof(char) * ((ft_lw(s, c, k) + 1)))))
			return (ft_free(str, i));
		while (s[k] != c && s[k] != '\0')
			str[i][j++] = s[k++];
		str[i][j] = '\0';
		i++;
	}
	str[i] = 0;
	return (str);
}