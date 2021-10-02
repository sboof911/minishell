/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:24:03 by amaach            #+#    #+#             */
/*   Updated: 2021/07/07 15:07:46 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_words(char const *s, char c)
{
	int		i;
	size_t	j;
	int		compt1;
	int		compt2;

	compt2 = 0;
	compt1 = 0;
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' && compt2 == 0)
			compt1++;
		if (s[i] == '\'' && compt1 == 0)
			compt2++;
		if (((s[i] == c && s[i + 1] != c && s[i + 1]) || (i == 0 && s[i] != c))
			&& (compt1 == 2 || compt1 == 0) && (compt2 == 2 || compt2 == 0))
			j++;
		if (compt1 == 2)
			compt1 = 0;
		if (compt2 == 2)
			compt2 = 0;
		i++;
	}
	return (j);
}

int	ft_lw(char const *s, char c, int i)
{
	size_t	j;
	int	compt1;
	int	compt2;

	compt2 = 0;
	compt1 = 0;
	j = 0;
	while ((s[i] != c && s[i] != '\0') || (compt1 == 1 && s[i] != '\0')
		|| (compt2 == 1 && s[i] != '\0'))
	{
		if (s[i] == '"' && compt2 == 0)
			compt1++;
		if (s[i] == '\'' && compt1 == 0)
			compt2++;
		i++;
		j++;
		if (compt1 == 2)
			compt1 = 0;
		if (compt2 == 2)
			compt2 = 0;
	}
	return (j);
}

void	*ft_free(char **s, int i)
{
	while (i--)
		free(s[i]);
	free(s);
	return (0);
}

char	**split_pipe(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;
	int		compt1;
	int		compt2;

	i = 0;
	k = 0;
	compt1 = 0;
	compt2 = 0;
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
		while ((s[k] != c && s[k] != '\0') || (compt1 == 1 && s[k] != '\0')
			|| (compt2 == 1 && s[k] != '\0'))
		{
			if (s[k] == '"' && compt2 == 0)
				compt1++;
			if (s[k] == '\'' && compt1 == 0)
				compt2++;
			str[i][j++] = s[k++];
			if (compt1 == 2)
				compt1 = 0;
			if (compt2 == 2)
				compt2 = 0;
		}
		str[i][j] = '\0';
		i++;
	}
	str[i] = 0;
	return (str);
}
