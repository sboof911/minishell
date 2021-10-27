/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:14:11 by amaach            #+#    #+#             */
/*   Updated: 2021/06/29 12:47:02 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**protection_malloc2(char **str, int compt)
{
	str = (char **)malloc(sizeof(char *) * (compt + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*protection_malloc1(char *str, int compt)
{
	str = (char *)malloc(sizeof(char) * (compt + 1));
	if (!str)
		return (NULL);
	return (str);
}
