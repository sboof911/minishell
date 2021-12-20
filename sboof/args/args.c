/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:22:17 by amaach            #+#    #+#             */
/*   Updated: 2021/12/20 10:32:29 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_sashell	*arg_parse(t_sashell *sashell, char **tab, t_env *env)
{
	while (tab[sashell->compt.position] != '\0'
		&& tab[sashell->compt.position][0] != '>'
		&& tab[sashell->compt.position][0] != '<')
	{
		if (ft_strchr(tab[sashell->compt.position], '$'))
			sashell = check_dollar(sashell, tab[sashell->compt.position],
					env, -1);
		else
		{
			sashell->tokens[sashell->compt.tokens]
				= ft_strdup(tab[sashell->compt.position]);
			sashell->tokens[sashell->compt.tokens]
				= delete_quotes(sashell->tokens[sashell->compt.tokens]);
		}
		sashell->compt.tokens++;
		sashell->compt.position++;
	}
	sashell->tokens[sashell->compt.tokens] = 0;
	return (sashell);
}

t_sashell	*help_final(t_sashell *sashell, int i, int j)
{
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
				else if (j > 1)
				{
					free(sashell->tokens[i]);
					sashell->tokens[i] = ft_strdup("-n");
				}
				i++;
			}
		}
		i++;
	}
	return (sashell);
}

t_sashell	*final_check(t_sashell *sashell)
{
	t_sashell	*tmp;
	int			i;

	tmp = sashell;
	while (sashell)
	{
		i = 0;
		sashell = help_final(sashell, i, 0);
		i = -1;
		while (sashell->red[++i])
			sashell->red[i] = delete_quotes(sashell->red[i]);
		sashell = sashell->next;
	}
	sashell = tmp;
	return (sashell);
}
