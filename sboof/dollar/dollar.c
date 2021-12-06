/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:18:55 by amaach            #+#    #+#             */
/*   Updated: 2021/12/06 23:19:26 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_sashell	*dollar_parse(t_sashell *sashell, char *tab, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, tab, ft_strlen(tab)) == 0
			&& ft_strncmp(env->key, tab, ft_strlen(env->key)) == 0)
		{
			sashell->tokens[sashell->compt.tokens]
				= ft_strjoin(sashell->tokens[sashell->compt.tokens],
					env->value);
			break ;
		}
		env = env->next;
	}
	sashell->compt.dollar++;
	return (sashell);
}

int	help_num_dollar(t_sashell *sashell, char *tab, int i)
{
	int	compt;

	while (ft_isdigit(tab[i]))
		i++;
	compt = i;
	while (tab[i] != '\0' && tab[i] != '$')
		i++;
	sashell->tokens[sashell->compt.tokens] = ft_substr(tab, compt, i - compt);
	sashell->tokens[sashell->compt.tokens]
		= delete_quotes(sashell->tokens[sashell->compt.tokens]);
	return (i);
}

int	help_check_dollar(t_sashell *sashell, char *tab, t_env *env, int i)
{
	int		compt;
	char	*help;

	compt = 0;
	if (tab[i] != '\0')
	{
		compt = i;
		if (ft_isdigit(tab[i]))
			i = help_num_dollar(sashell, tab, i);
		else if (tab[i] == '?')
			sashell->tokens[sashell->compt.tokens] = ft_itoa(g_exit_value);
		else
			while (ft_isalnum(tab[i++]));
		if (compt == i && tab[i] != '\'')
			sashell->tokens[sashell->compt.tokens]
				= ft_charjoin(sashell->tokens[sashell->compt.tokens], '$');
		else
		{
			help = ft_substr(tab, compt, i - compt);
			i--;
			sashell = dollar_parse(sashell, help, env);
			free(help);
		}
	}
	return (i);
}

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

int	some_shit(int *d_quotes, int *s_quotes, char *tab, int i)
{
	if (tab[i] == '"' && *s_quotes == 0)
	{
		*d_quotes = help_dollar_quotes(*d_quotes);
		return (1);
	}
	else if (tab[i] == '\'' && *d_quotes == 0)
	{
		*s_quotes = help_dollar_quotes(*s_quotes);
		return (1);
	}
	return (0);
}

t_sashell	*check_dollar(t_sashell *sashell, char *tab, t_env *env, int i)
{
	int		d_quotes;
	int		s_quotes;

	d_quotes = 0;
	s_quotes = 0;
	sashell->tokens[sashell->compt.tokens] = ft_strdup("");
	while (tab[++i] != '\0')
	{
		if (some_shit(&d_quotes, &s_quotes, tab, i))
			continue ;
		else if (tab[i] == '$' && s_quotes == 0)
		{
			i = help_check_dollar(sashell, tab, env, i + 1);
			if (tab[i] == '\0')
			{
				sashell->tokens[sashell->compt.tokens]
					= ft_charjoin(sashell->tokens[sashell->compt.tokens], '$');
				return (sashell);
			}
		}
		else
			sashell->tokens[sashell->compt.tokens]
				= ft_charjoin(sashell->tokens[sashell->compt.tokens], tab[i]);
	}
	return (sashell);
}
