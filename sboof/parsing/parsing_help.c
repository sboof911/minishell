/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:50:30 by amaach            #+#    #+#             */
/*   Updated: 2021/12/19 00:09:05 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_sashell	*initialize(t_sashell *sashell)
{
	sashell->compt.red = 0;
	sashell->has.red = 0;
	sashell->has.option = 0;
	sashell->has.arg = 0;
	sashell->compt.tokens = 0;
	sashell->compt.position = 0;
	sashell->compt.dollar = 0;
	sashell->red = NULL;
	sashell->tokens = NULL;
	return (sashell);
}

t_sashell	*count_every(t_sashell *sashell, char *tab)
{
	sashell->red = (char **)malloc((sizeof(char *)) * (1024));
	sashell->tokens = (char **)malloc((sizeof(char *)) * (1024));
	return (sashell);
}

char	**delete_spaces(char **tab)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (ft_count_tab(tab) + 1));
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] == ' ')
			j++;
		tmp[i] = ft_strdup(tab[i] + j);
		i++;
	}
	tmp[i] = 0;
	ft_free(tab, i);
	return (tmp);
}

int	ft_count_tab(char **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i] != NULL)
			i++;
	}
	return (i);
}

t_sashell	*final_check(t_sashell *sashell)
{
	t_sashell	*tmp;
	int			i;
	int			j;

	tmp = sashell;
	while (sashell)
	{
		i = 0;
		while (sashell->tokens[i])
		{
			if (!ft_strncmp(sashell->tokens[i], "echo", 4))
			{
				i++;
				if (!sashell->tokens[i])
					break ;
				while (sashell->tokens[i][0] == '-')
				{
					j = 1;
					while (sashell->tokens[i][j] == 'n')
						j++;
					if (sashell->tokens[i][j])
						break ;
					else
					{
						free(sashell->tokens[i]);
						sashell->tokens[i] = ft_strdup("-n");
					}
					i++;
				}
			}
			i++;
		}
		i = -1;
		while (sashell->red[++i])
			sashell->red[i] = delete_quotes(sashell->red[i]);
		sashell = sashell->next;
	}
	sashell = tmp;
	return (sashell);
}
