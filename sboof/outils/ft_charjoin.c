/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 11:52:42 by amaach            #+#    #+#             */
/*   Updated: 2021/10/20 11:32:23 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_charjoin(char *str, char c)
{
	char	*help;
	int		i;

	i = 0;
	help = malloc(ft_strlen(str) + 2);
	while (str[i] != '\0')
	{
		help[i] = str[i];
		i++;
	}
	help[i] = c;
	help[i + 1] = '\0';
	free (str);
	return (help);
}