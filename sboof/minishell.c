/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:10:34 by amaach            #+#    #+#             */
/*   Updated: 2021/07/06 18:45:06 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_has
{
	int		red;
	int		arg;
	int		option;
}				t_has;

typedef struct s_compt
{
	int		red;
	int		option;
	int		pipe;
	int		arg;
	int		position;
}				t_compt;

typedef struct	s_sashell 
{
	char				*command;
	char				**options;
	char				**arg;
	char				**red;
	int					in;
	int					out;
	struct s_has		has;
	struct s_compt		compt;
	struct s_sashell	*next;
}				t_sashell;

t_sashell	*check_file(t_sashell *sashell, char **tab, int i)
{
	if (ft_strlen(tab[sashell->compt.position]) <= 2 &&
		(tab[sashell->compt.position][1] == '>' || tab[sashell->compt.position][1] == '<'
		|| ft_strlen(tab[sashell->compt.position]) == 1))
	{
		sashell->compt.position++;
		sashell->red[sashell->has.red] = ft_strjoin(sashell->red[sashell->has.red], " ");
		sashell->red[sashell->has.red] = ft_strjoin(sashell->red[sashell->has.red], tab[sashell->compt.position]);
	}
	else
	{
		sashell->red[sashell->has.red] = ft_strjoin(sashell->red[sashell->has.red], " ");
		sashell->red[sashell->has.red] = ft_strjoin(sashell->red[sashell->has.red], tab[sashell->compt.position] + i);
	}
	return (sashell);
}

t_sashell	*rederiction_parse(t_sashell *sashell, char **tab)
{
	if (tab[sashell->compt.position][0] == '>' && tab[sashell->compt.position][1] != '>')
	{
		sashell->red[sashell->has.red] = ft_strdup(">");
		sashell = check_file(sashell, tab, 1);
	}
	else if (tab[sashell->compt.position][0] == '<' && tab[sashell->compt.position][1] != '<')
	{
		sashell->red[sashell->has.red] = ft_strdup("<");
		sashell = check_file(sashell, tab, 1);
	}
	if (tab[sashell->compt.position][0] == '>' && tab[sashell->compt.position][1] == '>')
	{
		sashell->red[sashell->has.red] = ft_strdup(">>");
		sashell = check_file(sashell, tab, 2);
	}
	else if (tab[sashell->compt.position][0] == '<' && tab[sashell->compt.position][1] == '<')
	{
		sashell->red[sashell->has.red] = ft_strdup("<<");
		sashell = check_file(sashell, tab, 2);
	}
	if (sashell->has.red < sashell->compt.red)
		sashell->has.red++;
	return (sashell);
}

t_sashell	*arg_parse(t_sashell *sashell, char **tab)
{
	int		i;

	i = 0;
	while (tab[sashell->compt.position] != '\0' && (tab[sashell->compt.position][0] != '>'
		|| tab[sashell->compt.position][0] != '<' || tab[sashell->compt.position][0] != '$'))
	{
		sashell->arg[i] = ft_strdup(tab[sashell->compt.position]);
		i++;
		sashell->compt.position++;
	}
	return (sashell);
}

t_sashell	*command_parse(t_sashell *sashell, char **tab)
{
	int		i;
	
	i = 0;
	sashell->command = ft_strdup(tab[sashell->compt.position]);
	if (tab[sashell->compt.position + 1])
	{
		sashell->compt.position++;
		if (tab[sashell->compt.position][0] == '-')
		{
			while (tab[sashell->compt.position] && tab[sashell->compt.position][0] == '-')
			{
				sashell->options[i] = ft_strdup(tab[sashell->compt.position]);
				i++;
				sashell->compt.position++;
			}
			sashell = arg_parse(sashell, tab);
			if (tab[sashell->compt.position] == '\0')
				sashell->compt.position--;
		}
		else
		{
			sashell = arg_parse(sashell, tab);
			if (tab[sashell->compt.position] == '\0')
				sashell->compt.position--;
		}
	}
	return (sashell);
}

t_sashell	*dollar_parse(t_sashell *sashell,  char **tab)
{
	printf("dollar");
	return (sashell);
}

t_sashell	*count_every(t_sashell *sashell, char **tab)
{
	int		i;
	int		quotes;

	quotes = 0;
	i = 0;
	while (tab[i] != '\0')
	{
		if (tab[i][0] == '"' || tab[i][0] == '\'')
		{
			if (quotes == 0)
				quotes++;
			else
				quotes--;
		}
		if ((tab[i][0] == '>' || tab[i][0] == '<') && quotes == 0)
		{
			if (ft_strlen(tab[i]) <= 2 && (ft_strlen(tab[i]) == 1
				|| tab[i][1] == '>' || tab[i][1] == '<'))
				i++;
			sashell->compt.red++;
		}
		else if (tab[i][0] == '-' && i >= 1 && tab[i - 1][0] && quotes == 0)
			sashell->compt.option++;
		else
			sashell->compt.arg++;
		i++;
	}
	sashell->red = (char **)malloc((sizeof(char *)) * (sashell->compt.red + 1));
	sashell->options = (char **)malloc((sizeof(char *)) * (sashell->compt.option + 1));
	sashell->arg = (char **)malloc((sizeof(char *)) * (sashell->compt.arg + 1));
	return (sashell);
}

t_sashell	*initialize(t_sashell *sashell)
{
	sashell->compt.option = 0;
	sashell->compt.red = 0;
	sashell->has.red = 0;
	sashell->has.option = 0;
	sashell->has.arg = 0;
	sashell->compt.position = 0;
	sashell->compt.arg = -1;
	sashell->command = NULL;
	sashell->arg = NULL;
	sashell->options = NULL;
	sashell->red = NULL;
	return (sashell);
}

t_sashell	*fill_in_the_blank(t_sashell *sashell, char *tab)
{
	char	**help;
	int	i = 0;

	sashell = initialize(sashell);
	help = ft_split(tab, ' ');
	sashell =  count_every(sashell, help);
	while (help[sashell->compt.position])
	{
		if (help[sashell->compt.position][0] == '<' || help[sashell->compt.position][0] == '>')
			sashell = rederiction_parse(sashell, help);
		else if (ft_isalpha(help[sashell->compt.position][0]))
			sashell = command_parse(sashell, help);
		else if  (help[sashell->compt.position][0] == '$')
			sashell = dollar_parse(sashell, help);
		else
		{
			printf("SASHELL: %s: command not found\n", help[0]);
			break ;
		}
		sashell->compt.position++;
	}
	if (sashell->arg)
	{
		while (i < sashell->compt.arg)
		{
			ft_putstr("arg[");
			ft_putnbr(i);
			ft_putstr("] ... ");
			ft_putstr(sashell->arg[i]);
			ft_putchar('\n');
			i++;
		}
	}
	i = 0;
	if (sashell->options)
	{
		while (i < sashell->compt.option)
		{
			ft_putstr("option[");
			ft_putnbr(i);
			ft_putstr("] ... ");
			ft_putstr(sashell->options[i]);
			ft_putchar('\n');
			i++;
		}
	}
	i = 0;
	if (sashell->red)
	{
		while (i < sashell->compt.red)
		{
			ft_putstr("red[");
			ft_putnbr(i);
			ft_putstr("] ... ");
			ft_putstr(sashell->red[i]);
			ft_putchar('\n');
			i++;
		}
	}
	i = 0;
	if (sashell->command != 0)
	{
		ft_putstr("command[");
		ft_putnbr(i);
		ft_putstr("] ... ");
		ft_putstr(sashell->command);
		ft_putchar('\n');
	}
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
