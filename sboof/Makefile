# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 14:53:47 by amaach            #+#    #+#              #
#    Updated: 2021/06/30 12:36:10 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =  -lreadline -ledit
NAME = minishell
SRC =  minishell.c ft_split.c outils_help.c ft_strdup.c ft_strlen.c \
		ft_isalpha.c

all:	$(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	

fclean:	clean
	rm -f $(NAME)

re:		fclean all