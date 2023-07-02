# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/04 14:40:40 by wismith           #+#    #+#              #
#    Updated: 2023/06/12 22:34:06 by wismith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PackReader

SRCS = main \
	start \
	init \
	utils \
	queue \
	parser \
	tree

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread -g3

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

ifeq ($(shell uname -s), Linux)
	DEF = -D LINUX
endif
ifeq ($(shell uname -s), Darwin)
	DEF = -D DARWIN
endif

$(OBJDIR)/%.o : srcs/%.c
	@printf "\033[A\033[2K\r"
	@mkdir -p $(OBJDIR)

	@tput setaf 2
	@printf "\tGenerating ... "
	@tput init

	$(CC) $(CFLAGS) $(DEF) -c $< -o $@

all : $(NAME)

$(NAME) : PRINTHEADER $(OBJ)
	@printf "\033[A\033[2K\r"
	@tput setaf 2
	@printf "\tGenerating ... "
	@tput init
	$(CC) $(CFLAGS) $(OBJ) $(DEF) -o $(NAME) -lpcap

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

PRINTHEADER :
	@tput setaf 2
	@printf " _____           _        _     _____                _           \n"
	@printf "|  __ \         | |      | |   |  __ \              | |          \n"
	@printf "| |__) |_ _  ___| | _____| |_  | |__) |___  __ _  __| | ___ _ __ \n"
	@printf "|  ___/ _  |/ __| |/ / _ \ __| |  _  // _ \/ _  |/ _  |/ _ \ '__|\n"
	@printf "| |  | (_| | (__|   <  __/ |_  | | \ \  __/ (_| | (_| |  __/ |   \n"
	@printf "|_|   \__,_|\___|_|\_\___|\__| |_|  \_\___|\__,_|\__,_|\___|_|   \n\n\n"
	@tput init

.PHONY : all clean fclean re