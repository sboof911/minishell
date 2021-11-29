# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 17:50:42 by eelaazmi          #+#    #+#              #
#    Updated: 2021/11/27 17:50:47 by eelaazmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEAKS = -g3 -fsanitize=address

FLAGS =  -lreadline -ledit  #/*-Wall -Wextra -Werror*/

NAME = minishell

SRC =  _minishell.c _builtin.c _echo.c _pwd.c  _cd.c _tools.c\
		cmd_export.c cmd_export_outil.c cmd_unset.c cmd_exit.c exec_others.c\
		sboof/outils/ft_split.c  sboof/outils/outils_help.c  sboof/outils/ft_strdup.c  sboof/outils/ft_strlen.c \
		sboof/outils/ft_isalpha.c  sboof/outils/ft_putchar.c  sboof/outils/ft_putstr.c  sboof/outils/ft_strjoin.c \
		sboof/outils/ft_putnbr.c  sboof/outils/split_pipe.c  sboof/outils/ft_strchr.c  sboof/outils/ft_substr.c \
		sboof/outils/ft_strncmp.c  sboof/minishell.c sboof/outils/ft_charjoin.c sboof/outils/ft_itoa.c\
		sboof/outils/ft_strrev.c\
		
OBJS = $(SRCS:%.c=%.o)

all:	$(NAME)

$(NAME) : $(SRC)
	gcc  $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJS)


fclean:	clean
	rm -f $(NAME)

re:		fclean all
