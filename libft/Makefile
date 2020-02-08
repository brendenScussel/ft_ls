# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bscussel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/02 14:58:19 by bscussel          #+#    #+#              #
#    Updated: 2019/12/29 18:53:13 by bscussel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ./libft.a

FTPF		= ./ftpf/libftprintf.a

FLAGS		= -c -Wall -Werror -Wextra

HEADER		= ./lib/libft.h

GNL-HEAD	= ./gnl/get_next_line.h

PF-HEAD		= ./ftpf/src/ft_printf.h

SRCFILES	= ./lib/err_prog.c \
				./lib/ft_bzero.c \
				./lib/ft_memset.c \
				./lib/ft_memcpy.c \
				./lib/ft_memccpy.c \
				./lib/ft_memmove.c \
				./lib/ft_memchr.c \
				./lib/ft_memcmp.c \
				./lib/ft_memalloc.c \
				./lib/ft_memdel.c \
				./lib/ft_strlen.c \
				./lib/ft_strdup.c \
				./lib/ft_strcpy.c \
				./lib/ft_strncpy.c \
				./lib/ft_strcat.c \
				./lib/ft_strncat.c \
				./lib/ft_strlcat.c \
				./lib/ft_strchr.c \
				./lib/ft_strrchr.c \
				./lib/ft_strstr.c \
				./lib/ft_strnstr.c \
				./lib/ft_strcmp.c \
				./lib/ft_strncmp.c \
				./lib/ft_strnew.c \
				./lib/ft_strdel.c \
				./lib/ft_strclr.c \
				./lib/ft_striter.c \
				./lib/ft_striteri.c \
				./lib/ft_strmap.c \
				./lib/ft_strmapi.c \
				./lib/ft_strequ.c \
				./lib/ft_strnequ.c \
				./lib/ft_strsub.c \
				./lib/ft_strjoin.c \
				./lib/ft_strtrim.c \
				./lib/ft_strsplit.c \
				./lib/ft_putchar.c \
				./lib/ft_putstr.c \
				./lib/ft_putendl.c \
				./lib/ft_putnbr.c \
				./lib/ft_putchar_fd.c \
				./lib/ft_putstr_fd.c \
				./lib/ft_putendl_fd.c \
				./lib/ft_putnbr_fd.c \
				./lib/ft_isspace.c \
				./lib/ft_isalpha.c \
				./lib/ft_isdigit.c \
				./lib/ft_isalnum.c \
				./lib/ft_isascii.c \
				./lib/ft_isprint.c \
				./lib/ft_toupper.c \
				./lib/ft_tolower.c \
				./lib/ft_atoi.c \
				./lib/ft_itoa.c \
				./lib/ft_nbr_size.c \
				./lib/ft_pow.c \
				./lib/ft_absol.c \
				./lib/ft_sqrt.c \
				./lib/ft_atoi_base.c \
				./lib/ft_itoa_base.c \
				./lib/ft_swap.c \
				./lib/ft_lstnew.c \
				./lib/ft_lstdel.c \
				./lib/ft_lstdelone.c \
				./lib/ft_lstadd.c \
				./lib/ft_lstiter.c \
				./lib/ft_lstmap.c \
				./lib/ft_lstrev.c \
				./gnl/get_next_line.c \

O_FILES		= *.o

all: $(NAME)

$(NAME): $(O_FILES)
		@echo "\033[0;35mBuilding Libft...\033[0m"
		ar rc $(NAME) obj/$(O_FILES)
		ranlib $(FTPF)
		ar rc $(NAME) ./ftpf/*.o
		ranlib $(NAME)

$(O_FILES): $(SRCFILES)
		$(MAKE) -C ftpf
		gcc $(FLAGS) -I=$(HEADER) -I=$(GNL-HEAD) -I=$(PF-HEAD) $(SRCFILES)
		mkdir obj
		mv $(O_FILES) ./obj/

clean:
		$(MAKE) clean -C ftpf
		rm -rf $(O_FILES) ./obj/$(O_FILES) ./obj

fclean: clean
		$(MAKE) fclean -C ftpf
		rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re