/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:22:17 by amaach            #+#    #+#             */
/*   Updated: 2021/12/06 23:22:25 by amaach           ###   ########.fr       */
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
