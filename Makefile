# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 17:50:42 by eelaazmi          #+#    #+#              #
#    Updated: 2021/12/20 22:08:38 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AFLAGS =  -lreadline -ledit -I/goinfre/amaach/.brew/opt/readline/include\
		-L/goinfre/amaach/.brew/opt/readline/lib -g -fsanitize=address #-Wall -Wextra -Werror 

MFLAGS =  -lreadline -ledit -I/goinfre/eelaazmi/.brew/opt/readline/include\
		-L/goinfre/eelaazmi/.brew/opt/readline/lib -Wall -Wextra -Werror

NAME = minishell

SRC =  	minishell.c\
		alchemist/_builtin.c alchemist/_echo.c alchemist/_pwd.c  alchemist/_cd.c alchemist/_tools.c\
		alchemist/cmd_export.c alchemist/cmd_export_outil.c alchemist/cmd_unset.c alchemist/cmd_exit.c\
		alchemist/exec_others.c alchemist/exec_pipe.c alchemist/exec_redire.c minishell_outils.c\
		alchemist/cmd_export_outil2.c alchemist/cmd_export_outil3.c alchemist/exec_others_outils.c\
		alchemist/_tools2.c alchemist/exec_pipe2.c minishell_outils2.c\
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
	gcc -g3  $(AFLAGS) $(LEAKS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJS)


fclean:	clean
	rm -f $(NAME)

re:		fclean all
