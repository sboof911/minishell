/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:10:34 by amaach            #+#    #+#             */
/*   Updated: 2021/06/29 18:30:54 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_sashell	*fill_in_the_blank(t_sashell *sashell, char *tab)
{
	char* tmp = tab; 
	tmp = NULL;
	return (sashell);
}

t_sashell	*parse_time(char **tab)
{
	t_sashell	*sashell;
	t_sashell	*tmp;
	int	i;

	if (!tab[0])
		return (NULL);
	sashell = (t_sashell *)malloc(sizeof(t_sashell));
	tmp = (t_sashell *)malloc(sizeof(t_sashell));
	i = 0;
	if (!sashell)
		return (NULL);
	tmp = fill_in_the_blank(sashell, tab[0]);
	while (tab[i])
	{
		sashell = fill_in_the_blank(sashell, tab[i]);
		if (tab[i + 1])
		{
			sashell->next = (t_sashell *)malloc(sizeof(t_sashell));
			if (!sashell->next)
				return (NULL);
			sashell = sashell->next;
		}
		i++;
	}
	return NULL;
}

char	**delete_spaces(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] == ' ')
			j++;
		tab[i] = ft_strdup(tab[i] + j);
		i++;
	}
	return (tab);
}

int	main(void)
{
	char	*line;
	char	**tab;

	while (1)
	{
		line = readline("minishell ▸ ");
		add_history(line);
		tab = ft_split(line, '|');
		tab = delete_spaces(tab);
		parse_time(tab);
	}
	return (0);
}
