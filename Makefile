# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 14:53:47 by amaach            #+#    #+#              #
#    Updated: 2021/11/15 23:37:06 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =  -lreadline -ledit -g #-fsanitize=address
NAME = minishell

SRC =  _minishell.c _builtin.c _echo.c _pwd.c  _cd.c _tools.c\
		 sboof/outils/ft_split.c  sboof/outils/outils_help.c  sboof/outils/ft_strdup.c  sboof/outils/ft_strlen.c \
		 sboof/outils/ft_isalpha.c  sboof/outils/ft_putchar.c  sboof/outils/ft_putstr.c  sboof/outils/ft_strjoin.c \
		 sboof/outils/ft_putnbr.c  sboof/outils/split_pipe.c  sboof/outils/ft_strchr.c  sboof/outils/ft_substr.c \
		 sboof/outils/ft_strncmp.c  sboof/minishell.c sboof/outils/ft_charjoin.c sboof/outils/ft_itoa.c\
		 sboof/outils/ft_strrev.c\
		  cmd_export.c cmd_export_outil.c\

all:	$(NAME)

$(NAME) : $(SRC)
	gcc  $(FLAGS) $(SRC) -o $(NAME)

clean:
	

fclean:	clean
	rm -f $(NAME)

re:		fclean all
