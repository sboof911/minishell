/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:21:13 by amaach            #+#    #+#             */
/*   Updated: 2021/07/05 17:29:15 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

char	**protection_malloc2(char **str, int compt);
char	*protection_malloc1(char *str, int compt);
void    *ft_free(char **s, int i);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
int		ft_strlen(char *str);
int		ft_isalpha(int c);
void	ft_putstr(char *s);
void	ft_putchar(char c);

#endif