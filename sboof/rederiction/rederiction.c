/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederiction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:16:36 by amaach            #+#    #+#             */
/*   Updated: 2021/12/06 23:19:29 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_sashell	*check_file(t_sashell *sashell, char *tab, int i)
{
	if (tab[0] != '>' && tab[0] != '<')
		i = 0;
	sashell->red[sashell->has.red]
		= ft_strjoin(sashell->red[sashell->has.red], " ");
	sashell->red[sashell->has.red]
		= ft_strjoin(sashell->red[sashell->has.red], tab + i);
	return (sashell);
}

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
		if (tab[i] == '"')
			compt1++;
		if (tab[i] == '\'')
			compt2++;
		i++;
	}
	if (compt1 % 2 == 1 || compt2 % 2 == 1)
		ft_putstr("quotes non fermer");
	return (compt1 + compt2);
}

char	*delete_quotes(char *tab)
{
	int		i;
	int		compt;
	int		j;
	char	*str;

	j = -1;
	compt = 0;
	compt = count_quotes(tab);
	str = (char *)malloc(ft_strlen(tab) - compt + 1);
	i = -1;
	while (tab[++i] != '\0')
	{
		if (tab[i] != '"' && tab[i] != '\'')
			str[++j] = tab[i];
	}
	str[++j] = '\0';
	free(tab);
	return (str);
}

t_sashell	*rederiction_parse(t_sashell *sashell, char *tab, char red)
{
	if ((tab[0] == '>' && tab[1] != '>') || red == '>')
	{
		sashell->red[sashell->has.red] = ft_strdup("1>");
		sashell = check_file(sashell, tab, 1);
	}
	else if ((tab[0] == '<' && tab[1] != '<') || red == '<')
	{
		sashell->red[sashell->has.red] = ft_strdup("1<");
		sashell = check_file(sashell, tab, 1);
	}
	if ((tab[0] == '>' && tab[1] == '>') || red == '7')
	{
		sashell->red[sashell->has.red] = ft_strdup("2>");
		sashell = check_file(sashell, tab, 2);
	}
	else if ((tab[0] == '<' && tab[1] == '<') || red == '4')
	{
		sashell->red[sashell->has.red] = ft_strdup("2<");
		sashell = check_file(sashell, tab, 2);
	}
	sashell->has.red++;
	return (sashell);
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

int	help_rederiction(t_sashell *sashell, char **tab, int i)
{
	while (tab[sashell->compt.position][i] == '>'
		|| tab[sashell->compt.position][i] == '<')
		i++;
	while (tab[sashell->compt.position][i] != '<'
		&& tab[sashell->compt.position][i] != '>'
		&& tab[sashell->compt.position][i] != '\0')
		i++;
	return (i);
}

int	help_red(char **tab, int i, t_sashell *sashell, int remember)
{
	if (tab[sashell->compt.position][i] != '\0')
		remember = i;
	return (remember);
}

t_sashell	*parse_red(t_sashell *sashell, char **tab, int i, int remember)
{
	char	*help;
	char	red;

	while (tab[sashell->compt.position][i] != '\0')
	{
		red = rederiction_sign(tab[sashell->compt.position]);
		sashell->compt.position += (red != 0);
		i = help_rederiction(sashell, tab, i);
		help = ft_substr(tab[sashell->compt.position], remember, i - remember);
		if (!red)
		{
			red = rederiction_sign(help);
			if (red)
			{
				free(help);
				sashell->compt.position++;
				i = help_rederiction(sashell, tab, 0);
				help = ft_substr(tab[sashell->compt.position], 0, i);
			}
		}
		sashell = rederiction_parse(sashell, help, red);
		free(help);
		remember = help_red(tab, i, sashell, remember);
	}
	return (sashell);
}
