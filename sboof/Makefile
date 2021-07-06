# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 14:53:47 by amaach            #+#    #+#              #
#    Updated: 2021/07/05 17:01:53 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


FLAGS =  -Wall -Wextra -Werror -lreadline -ledit

NAME = minishell

FLAGS =  -lreadline -ledit

NAME = minishell


SRC =  minishell.c ft_split.c outils_help.c ft_strdup.c ft_strlen.c \
		ft_isalpha.c ft_putchar.c ft_putstr.c

SRC =  minishell.c ft_split.c outils_help.c ft_strdup.c ft_strlen.c\
	   ../alchemist/*.c\

all: $(NAME)

$(NAME) : $(SRC)
	@echo "\n"
	@echo "\033[0;32mCompiling minishell..."
	@gcc $(FLAGS) $(SRC) -o $(NAME)
	@echo "\n\033[0mDone !"

clean:
	

fclean:	clean
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re:		fclean all