/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederiction_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:47:19 by amaach            #+#    #+#             */
/*   Updated: 2021/12/19 02:51:58 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_quotes(char *tab)
{
	int		i;
	int		compt1;
	int		compt2;

	i = 0;
	compt1 = 0;
	compt2 = 0;
	while (tab[i] != '\0')
	{
		if (tab[i] == '"' && compt2 % 2 == 0)
			compt1++;
		if (tab[i] == '\'' && compt1 % 2 == 0)
			compt2++;
		i++;
	}
	if (compt1 % 2 == 1 || compt2 % 2 == 1)
		ft_putstr("quotes non fermer");
	return (compt1 + compt2);
}

char	rederiction_sign(char *tab)
{
	char	red;

	red = 0;
	if (ft_strlen(tab) == 1
		|| (ft_strlen(tab) == 2 && (tab[1] == '<' || tab[1] == '>')))
	{
		if (ft_strlen(tab) == 1)
		{
			if (tab[0] == '<')
				red = '<';
			else
				red = '>';
		}
		else
		{
			if (tab[0] == '<')
				red = '4';
			else
				red = '7';
		}
	}
	return (red);
}

int	help_red(char **tab, int i, t_sashell *sashell, int remember)
{
	if (tab[sashell->compt.position][i] != '\0')
		remember = i;
	return (remember);
}
