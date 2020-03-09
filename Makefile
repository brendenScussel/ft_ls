# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bscussel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 22:21:43 by bscussel          #+#    #+#              #
#    Updated: 2020/03/07 03:46:57 by bscussel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

CFLAGS = -Wall -Wextra -Werror

HEADER = ./ft_ls.h

CFILES = ./ft_ls_main.c \
		./ft_ls_0_util.c \
		./ft_ls_1_read.c \
		./ft_ls_2_print.c \
		./ft_ls_3_sort.c \
		./ft_ls_4_single.c \

LIBFT = ./libft/libft.a

OBJ_DIR = obj

all: $(NAME)

$(NAME):
	@echo "\033[0;35mBuilding FtLs...\033[0m"
	$(MAKE) -s -C libft
	ranlib $(LIBFT)
	$(CC) $(CFLAGS) -I=$(HEADER) -o $(NAME) $(CFILES) $(LIBFT)

clean :
	@echo "\033[0;35mCleaning Object Files...\033[0m"
	$(MAKE) -s clean -C libft
	rm -rf $(O_FILES) obj/$(O_FILES) obj

fclean :
	@echo "\033[0;35mCleaning EVERYTHING...\033[0m"
	$(MAKE) -s fclean -C libft
	rm -rf $(NAME) $(O_FILES) obj/$(O_FILES) obj $(LIBFT)

re: fclean all

.PHONY: clean fclean all re
