/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:37:32 by amaach            #+#    #+#             */
/*   Updated: 2021/12/22 15:39:29 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*generate_random_value(void)
{
	int				fd;
	unsigned int	randval;
	char			*rand_string;
	char			*r_string;
	char			*tmp;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &randval, sizeof(randval));
	close(fd);
	rand_string = ft_itoa(randval);
	tmp = ft_strdup("/tmp/heredoc-");
	r_string = ft_strjoin(tmp, rand_string);
	free (rand_string);
	return (r_string);
}

static void	processe(int signum)
{
	if (signum == SIGQUIT)
	{
		printf("Quit :\n");
		g_.exit_value = 131;
		exit (0);
	}
	else if (signum == SIGINT)
	{
		ft_putchar('\n');
		g_.exit_value = 130;
	}
	g_.pid = 0;
}

void	quit_handler(int signum)
{
	if ((signum == SIGINT || signum == SIGQUIT) && g_.pid != 0)
		processe(signum);
	else
	{
		if (signum == SIGINT)
		{
			ft_putchar('\n');
			rl_on_new_line();
			rl_replace_line("", STDIN_FILENO);
			rl_redisplay();
			g_.exit_value = 1;
		}
		else if (signum == SIGQUIT)
		{
			ft_putchar_fd('\r', STDERR_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

char	*heredoc(t_sashell *sashell, int i)
{
	int		fd;
	char	*line;
	char	*random_string;

	random_string = generate_random_value();
	fd = open(random_string, O_CREAT | O_RDWR, S_IRWXU);
	while (420)
	{
		line = readline("?> ");
		if (!line || !ft_strncmp(line, sashell->red[i] + 3,
				ft_strlen(sashell->red[i] + 3)))
		{
			if (line)
				free(line);
			close(fd);
			return (random_string);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (NULL);
}

t_sashell	*red_open(t_sashell *sashell)
{
	int			i;
	char		*tmp;
	t_sashell	*help;

	help = sashell;
	while (sashell)
	{
		i = 0;
		while (sashell->red[i] != 0)
		{
			if (sashell->red[i][0] == '2' && sashell->red[i][1] == '<')
			{
				tmp = heredoc(sashell, i);
				free(sashell->red[i]);
				sashell->red[i] = ft_strdup("1< ");
				sashell->red[i] = ft_strjoin(sashell->red[i], tmp);
				free(tmp);
			}
			i++;
		}
		sashell = sashell->next;
	}
	sashell = help;
	return (sashell);
}
