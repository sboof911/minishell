/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:54:22 by amaach            #+#    #+#             */
/*   Updated: 2021/12/18 02:26:24 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	help_check_sytax(char *line, int i)
{
	if (check_quotes(line, i) != 1)
	{
		ft_putstr("SASHELL : Syntax Error // quotes not closed\n");
		return (0);
	}
	if (check_red(line, i - 1) != 1)
	{
		ft_putstr("SASHELL : Syntax Error // redirections\n");
		return (0);
	}
	return (1);
}
