/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:54:22 by amaach            #+#    #+#             */
/*   Updated: 2021/12/20 10:52:03 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	help_check_sytax(char *line, int i)
{
	if (check_quotes(line, i) != 1)
	{
		g_exit_value = 258;
		ft_putstr("SASHELL : Syntax error\n");
		return (0);
	}
	if (check_red(line, i - 1) != 1)
	{
		g_exit_value = 258;
		ft_putstr("SASHELL : Syntax error near unexpected token\n");
		return (0);
	}
	return (1);
}
