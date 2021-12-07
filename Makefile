# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 17:50:42 by eelaazmi          #+#    #+#              #
#    Updated: 2021/12/07 15:31:59 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEAKS = -g #-fsanitize=address

FLAGS =  -lreadline -ledit -I/goinfre/amaach/.brew/opt/readline/include \
		-L/goinfre/amaach/.brew/opt/readline/lib #-Wall -Wextra -Werror # change to your goinfree 

NAME = minishell

SRC =  _minishell.c _builtin.c _echo.c _pwd.c  _cd.c _tools.c\
		cmd_export.c cmd_export_outil.c cmd_unset.c cmd_exit.c exec_others.c exec_pipe.c\
		sboof/outils/ft_split.c sboof/outils/outils_help.c sboof/outils/ft_strdup.c sboof/outils/ft_strlen.c \
		sboof/outils/ft_isalpha.c sboof/outils/ft_putchar.c sboof/outils/ft_putstr.c sboof/outils/ft_strjoin.c \
		sboof/outils/ft_putnbr.c sboof/outils/split_pipe.c sboof/outils/ft_strchr.c sboof/outils/ft_substr.c \
		sboof/outils/ft_strncmp.c sboof/outils/ft_charjoin.c sboof/outils/ft_itoa.c sboof/outils/ft_strrev.c \
		sboof/rederiction/rederiction.c sboof/rederiction/rederiction_help.c sboof/parsing/parsing.c \
		sboof/parsing/parsing_help.c sboof/dollar/dollar.c sboof/dollar/dollar_help.c sboof/args/args.c \
		sboof/errors/errors.c sboof/errors/errors_help.c sboof/herdoc/herdoc.c
		
OBJS = $(SRCS:%.c=%.o)

all:	$(NAME)

$(NAME) : $(SRC)
	gcc  $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJS)


fclean:	clean
	rm -f $(NAME)

re:		fclean all
