# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 14:53:47 by amaach            #+#    #+#              #
#    Updated: 2021/07/09 20:07:17 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =  -lreadline -ledit -fsanitize=address
NAME = minishell
SRC =  minishell.c ../sboof/ft_split.c ../sboof/outils_help.c ../sboof/ft_strdup.c ../sboof/ft_strlen.c \
		../sboof/ft_isalpha.c ../sboof/ft_putchar.c ../sboof/ft_putstr.c ../sboof/ft_strjoin.c ../sboof/ft_putnbr.c \
		../sboof/split_pipe.c ../sboof/ft_strchr.c ../sboof/ft_substr.c ../sboof/ft_strncmp.c builtin.c \
		../sboof/minishell.c

all:	$(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	

fclean:	clean
	rm -f $(NAME)

re:		fclean all