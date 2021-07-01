/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:10:34 by amaach            #+#    #+#             */
/*   Updated: 2021/07/01 12:48:25 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_sashell 
{
	char	*command;
	char	**options;
	char	**arg;
	int		has_arg;
	char	**red;
	int		has_red;
	int		in;
	int		out;
	struct s_sashell	*next;
}				t_sashell;

t_sashell	*rederiction_parse(t_sashell *sashell, char **tab)
{
	int i;
	int	compt;

	i = 0;
	compt = ft_strlen(tab[0]);
	if (compt == 1)
	{
		if (tab[0][0] == '>')
		{
			
		}
		else
		{
			
		}
	}
	else if (compt == 2)
	{
		if (tab[0][0] == '>' && tab[0][1] == '>')
		{

		}
		else if (tab[0][0] == '<' && tab[0][1] == '<')
		{

		}
		else
		{
			// TODO Error 
		}
	}
	else
	{
		//TODO Error multiple <><>
	}
	return (sashell);
}

t_sashell	*command_parse(t_sashell *sashell, char **tab)
{
	printf("com");
	return (sashell);
}

t_sashell	*dollar_parse(t_sashell *sashell, char **tab)
{
	printf("dollar");
	return (sashell);
}

t_sashell	*fill_in_the_blank(t_sashell *sashell, char *tab)
{
	char	**help;

	help = ft_split(tab, ' ');
	if (help[0][0] == '<' || help[0][0] == '>')
		sashell = rederiction_parse(sashell, help);
	else if (ft_isalpha(help[0][0]))
		sashell = command_parse(sashell, help);
	else if  (help[0][0] == '$')
		sashell = dollar_parse(sashell, help);
	else
		printf("SASHELL: %s: command not found\n", help[0]);
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
	i = 1;
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
	return (sashell);
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
	t_sashell	*sashell;

	while (1)
	{
		line = readline("SASHELL $");
		add_history(line);
		tab = ft_split(line, '|');
		tab = delete_spaces(tab);
		sashell = parse_time(tab);
	}
	return (0);
}
