/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:53:16 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/11/27 17:53:19 by eelaazmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	int				sign;
	long long		value;

	sign = 1;
	value = 0;
	while (*str == ' ' || *str == '\f' || *str == '\n' || \
			*str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	if (sign == 1)
		return (value);
	else
		return (-value);
}

static int	ft_isdigit_str(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (!ft_isdigit(str[idx]))
			return (0);
		idx++;
	}
	return (1);
}

void	ft_exit(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2 && ft_isdigit_str(argv[1]))
		exit(ft_atoi(argv[1]));
	else if (argc > 2 && ft_isdigit_str(argv[1]))
		ft_putendl_fd("bash: exit: too many arguments", 1);
	else
	{
		ft_putstr_fd("bash: exit: numeric argument required", 1);
		exit(2);
	}
}
