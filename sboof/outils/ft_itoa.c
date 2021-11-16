/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:33:10 by amaach            #+#    #+#             */
/*   Updated: 2021/11/15 23:34:25 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_len(int n, long a)
{
	int		i;

	i = 0;
	if (n < 0)
		i++;
	while (a)
	{
		a /= 10;
		i++;
	}
	return (i);
}

static char	*ft_str(int n, long a, int i, int sign)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_len(n, a) + 1));
	if (!str)
		return (0);
	while (a > 0)
	{
		str[i] = a % 10 + '0';
		a /= 10;
		i++;
	}
	if (sign)
		str[i++] = '-';
	str[i++] = '\0';
	ft_strrev(str);
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	int		sign;
	long	a;
	char	*str;

	sign = 0;
	i = 0;
	a = n;
	if (n == 0)
	{
		str = malloc(2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n < 0)
	{
		sign = n;
		a *= -1;
	}
	return (ft_str(n, a, i, sign));
}
