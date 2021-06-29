/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:24:03 by amaach            #+#    #+#             */
/*   Updated: 2021/06/29 14:27:45 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_words(char *s)
{
	int	i;
	int	j;
}

char	**split_pipe(char *s)
{
	char	**str;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * ((ft_count_words(s) + 1)));
}
