# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 14:53:47 by amaach            #+#    #+#              #
#    Updated: 2021/10/27 19:38:41 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =  -lreadline -ledit -g #-fsanitize=address
NAME = minishell
SRC =  _minishell.c _builtin.c _echo.c _pwd.c  _cd.c _tools.c\
		 sboof/outils/ft_split.c  sboof/outils/outils_help.c  sboof/outils/ft_strdup.c  sboof/outils/ft_strlen.c \
		 sboof/outils/ft_isalpha.c  sboof/outils/ft_putchar.c  sboof/outils/ft_putstr.c  sboof/outils/ft_strjoin.c \
		 sboof/outils/ft_putnbr.c  sboof/outils/split_pipe.c  sboof/outils/ft_strchr.c  sboof/outils/ft_substr.c \
		 sboof/outils/ft_strncmp.c  sboof/minishell.c sboof/outils/ft_charjoin.c\

all:	$(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	

fclean:	clean
	rm -f $(NAME)

re:		fclean all
