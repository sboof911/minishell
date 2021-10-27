# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 14:53:47 by amaach            #+#    #+#              #
#    Updated: 2021/07/07 18:31:06 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =  -lreadline -ledit -fsanitize=address
NAME = minishell
SRC =  minishell.c ft_split.c outils_help.c ft_strdup.c ft_strlen.c \
		ft_isalpha.c ft_putchar.c ft_putstr.c ft_strjoin.c ft_putnbr.c \
		split_pipe.c ft_strchr.c ft_substr.c ft_strncmp.c

all:	$(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	

fclean:	clean
	rm -f $(NAME)

re:		fclean all