/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:40:17 by amaach            #+#    #+#             */
/*   Updated: 2021/12/06 23:53:26 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_sashell	*command_parse(t_sashell *sashell, char **tab, t_env *env)
{
	sashell->tokens[sashell->compt.tokens++]
		= ft_strdup(tab[sashell->compt.position++]);
	if (tab[sashell->compt.position])
	{
		if (tab[sashell->compt.position][0] == '-')
		{
			while (tab[sashell->compt.position]
				&& tab[sashell->compt.position][0] == '-')
			{
				sashell->tokens[sashell->compt.tokens]
					= ft_strdup(tab[sashell->compt.position]);
				sashell->compt.tokens++;
				sashell->compt.position++;
			}
			sashell = arg_parse(sashell, tab, env);
		}
		else
			sashell = arg_parse(sashell, tab, env);
	}
	return (sashell);
}

t_sashell	*fill_in_the_blank(t_sashell *sashell, char *tab, t_env *env)
{
	char	**help;

	sashell = initialize(sashell);
	help = split_pipe(tab, ' ');
	sashell = count_every(sashell, tab);
	while (help[sashell->compt.position])
	{
		if (help[sashell->compt.position][0] == '<'
			|| help[sashell->compt.position][0] == '>')
		{
			sashell = parse_red(sashell, help, 0, 0);
			sashell->compt.position++;
		}
		else if (ft_isalpha(help[sashell->compt.position][0])
			|| sashell->compt.tokens > 0)
			sashell = command_parse(sashell, help, env);
	}
	sashell->tokens[sashell->compt.tokens] = 0;
	sashell->red[sashell->has.red] = 0;
	ft_free(help, sashell->compt.position);
	return (sashell);
}

t_sashell	*next_sashell(t_sashell *sashell, t_env *env, char **tab)
{
	int		i;

	i = 1;
	sashell = sashell->next;
	while (tab[i])
	{
		sashell = fill_in_the_blank(sashell, tab[i], env);
		if (tab[i + 1])
		{
			sashell->next = (t_sashell *)malloc(sizeof(t_sashell));
			if (!sashell->next)
				return (NULL);
			sashell = sashell->next;
		}
		i++;
	}
	return (sashell);
}

t_sashell	*parse_time(char **tab, t_env *env)
{
	t_sashell	*sashell;
	t_sashell	*tmp;

	if (!tab[0])
		return (NULL);
	sashell = (t_sashell *)malloc(sizeof(t_sashell));
	if (!sashell)
		return (NULL);
	sashell = fill_in_the_blank(sashell, tab[0], env);
	tmp = sashell;
	sashell->next = (t_sashell *)malloc(sizeof(t_sashell));
	if (!sashell->next)
		return (NULL);
	if (!tab[1])
	{
		free(sashell->next);
		sashell->next = NULL;
		return (sashell);
	}
	sashell = next_sashell(sashell, env, tab);
	sashell->next = NULL;
	sashell = tmp;
	return (sashell);
}

t_sashell	*parse_function(t_sashell *sashell, t_env *env, char *line)
{
	char	**tab;

	if (check_sytaxerr(line) == 1)
	{
		tab = split_pipe(line, '|');
		tab = delete_spaces(tab);
		sashell = parse_time(tab, env);
		ft_free(tab, ft_count_tab(tab));
		red_open(sashell);
		free(line);
		return (sashell);
	}
	return (NULL);
}
