/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:10:34 by amaach            #+#    #+#             */
/*   Updated: 2021/07/05 18:22:37 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD


t_sashell	*fill_in_the_blank(t_sashell *sashell, char *tab)
{
	char* tmp = tab; 
	tmp = NULL;
=======
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

void	ft_malloc(char **tab, int compt)
{
	
}

t_sashell	*check_file(t_sashell *sashell, char **tab, int i)
{
	// int		compt;

	// compt = ft_strlen(tab[i]);
	// if (compt == 1 || compt == 2)
	// {
	// 	sashell->red[1] = 
	// }
	// else
	// {
	// 	if (tab[i][1] != '>' && tab[i][1] != '<')
	// }
	return (sashell);
}

t_sashell	*rederiction_parse(t_sashell *sashell, char **tab, int i)
{
	sashell->has.red = 1;
	if (tab[i][0] == '>' && tab[i][1] != '>')
	{
		sashell->red[0][0] = ft_strdup(">");
		sashell = check_file(sashell, tab, i);
	}
	else if (tab[i][0] == '<' && tab[i][1] != '<')
	{
		sashell->red[0][0] = ft_strdup("<");
		sashell = check_file(sashell, tab, i);
	}
	if (tab[i][0] == '>' && tab[i][1] == '>')
	{
		sashell->red[0][0] = ft_strdup(">>");
		sashell = check_file(sashell, tab, i);
	}
	else if (tab[i][0] == '<' && tab[i][1] == '<')
	{
		sashell->red[0][0] = ft_strdup("<<");
		sashell = check_file(sashell, tab, i);
	}
	ft_putstr(sashell->red[0]);
	return (sashell);
}

t_sashell	*command_parse(t_sashell *sashell, char **tab)
{
	
	printf("com");
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

	i = 0;
	while (tab[i] != '\0')
	{
		if (tab[i][0] == '>' || tab[i][0] == '<')
			sashell->compt.red++;
		else if (tab[i][0] == '-')
			sashell->compt.option++;
		else
			sashell->compt.arg++;
		i++;
	}
	sashell->red = (char **)malloc(sashell->compt.red + 1);
	sashell->options = (char **)malloc(sashell->compt.option + 1);
	return (sashell);
}

t_sashell	*initialize(t_sashell *sashell)
{
	sashell->compt.option = 0;
	sashell->compt.red = 0;
	sashell->has.red = 0;
	sashell->has.option = 0;
	sashell->has.arg = 0;
}

t_sashell	*fill_in_the_blank(t_sashell *sashell, char *tab)
{
	char	**help;

	sashell = initialize(sashell);
	help = ft_split(tab, ' ');
	sashell =  count_every(sashell, help);
	if (help[0][0] == '<' || help[0][0] == '>')
		// sashell = rederiction_parse(sashell, help, 0);
	else if (ft_isalpha(help[0][0]))
		sashell = command_parse(sashell, help);
	else if  (help[0][0] == '$')
		sashell = dollar_parse(sashell, help);
	else
		printf("SASHELL: %s: command not found\n", help[0]);
>>>>>>> bb10c4b349bbc7dfcd391c3904c653d81c071784
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
<<<<<<< HEAD
	i = 0;
=======
	i = 1;
>>>>>>> bb10c4b349bbc7dfcd391c3904c653d81c071784
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
<<<<<<< HEAD
	return NULL;
=======
	return (sashell);
>>>>>>> bb10c4b349bbc7dfcd391c3904c653d81c071784
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
		line = readline("minishell ▸ ");
		add_history(line);
		tab = ft_split(line, '|');
		tab = delete_spaces(tab);
		sashell = parse_time(tab);
	}
	return (0);
}
