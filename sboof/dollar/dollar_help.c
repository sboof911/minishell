/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:56:21 by amaach            #+#    #+#             */
/*   Updated: 2021/12/06 23:56:46 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	help_dollar_quotes(int d_q)
{
	if (d_q == 0)
		d_q = 1;
	else
		d_q = 0;
	return (d_q);
}

t_sashell	*help_norm_dollar(t_sashell *sashell, char *tab, int i)
{
	if (tab[i] == '\0')
	{
		sashell->tokens[sashell->compt.tokens]
			= ft_charjoin(sashell->tokens[sashell->compt.tokens], '$');
	}
	return (sashell);
}
