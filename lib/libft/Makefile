# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: test <test@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 04:23:57 by bmoll-pe          #+#    #+#              #
#    Updated: 2023/04/04 16:06:33 by test             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =		ft_atoi.c		ft_memmove.c	ft_strlcpy.c	\
			ft_bzero.c		ft_memset.c		ft_strlen.c		\
			ft_calloc.c		ft_putchar_fd.c	ft_strmapi.c	\
			ft_isalnum.c	ft_putendl_fd.c	ft_strncmp.c	\
			ft_isalpha.c	ft_putnbr_fd.c	ft_strnstr.c	\
			ft_isascii.c	ft_putstr_fd.c	ft_strrchr.c	\
			ft_isdigit.c	ft_split.c		ft_strrspn.c	\
			ft_isprint.c	ft_strchr.c		ft_strspn.c		\
			ft_itoa.c		ft_strdup.c		ft_strtrim.c	\
			ft_memchr.c		ft_striteri.c	ft_substr.c		\
			ft_memcmp.c		ft_strjoin.c	ft_tolower.c	\
			ft_memcpy.c		ft_strlcat.c	ft_toupper.c	\
			ft_isspace.c	ft_lstnew_bonus.c				\
			ft_lstadd_front_bonus.c		ft_lstsize_bonus.c	\
			ft_lstlast_bonus.c	ft_lstadd_back_bonus.c		\
			ft_lstdelone_bonus.c	ft_lstclear_bonus.c		\
			ft_lstiter_bonus.c	ft_lstmap_bonus.c

OBJS =		$(SRCS:.c=.o)

FLAGS =		-g -Werror -Wextra -Wall -c

CC = 		gcc

LIBR = 		libft.h

all:		$(NAME)

# Colors

DEL_LINE =	\033[2K
DEF_COLOR =	\033[0;39m
GRAY =		\033[0;90m
RED =		\033[0;91m
GREEN =		\033[0;92m
YELLOW =	\033[0;93m
BLUE =		\033[0;94m
MAGENTA =	\033[0;95m
CYAN =		\033[0;96m
WHITE =		\033[0;97m

all:		$(NAME)

%.o: %.c	$(LIBR)
			@printf "$(DEL_LINE)\r$(DEF_COLOR)[LIBFT] compiling: $<"
			@$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(LIBR)
			@printf "$(DEL_LINE)\r$(DEF_COLOR)[LIBFT] compiling: $<"
			@ar -rcs $(NAME) $(OBJS)
			@printf "$(DEL_LINE)\r$(BOLD)$(DARK_GREEN)LIBFT COMPILED ✅$(DEF_COLOR)\n"

clean:
			@rm -f	$(OBJS)

fclean:		clean
			@rm -f	$(NAME)

re:			fclean all

.PHONY: all clean fclean re
