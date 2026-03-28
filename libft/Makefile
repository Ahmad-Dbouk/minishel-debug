# **************************************************************************** #
#																			  #
#														 :::	  ::::::::	#
#	Makefile										   :+:	  :+:	:+:	#
#													 +:+ +:+		 +:+	  #
#	By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		 #
#												 +#+#+#+#+#+   +#+			#
#	Created: 2025/06/14 17:19:50 by adbouk			#+#	#+#			  #
#	Updated: 2025/06/14 17:20:03 by adbouk		   ###   ########.fr		#
#																			  #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_toupper.c ft_tolower.c ft_substr.c ft_strtrim.c ft_strrchr.c \
	  ft_strnstr.c ft_strncmp.c ft_strmapi.c ft_strlen.c ft_strlcpy.c \
	  ft_strlcat.c ft_strjoin.c ft_striteri.c ft_strdup.c ft_strchr.c \
	  ft_split.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_putchar_fd.c \
	  ft_memset.c ft_memcpy.c ft_memcmp.c ft_memchr.c ft_memmove.c ft_itoa.c \
	  ft_isprint.c ft_isdigit.c ft_isascii.c ft_isalpha.c ft_isalnum.c \
	  ft_calloc.c ft_bzero.c ft_atoi.c ft_strcmp.c

OBJ = $(SRC:.c=.o)

BONUS_SRC = ft_lstsize.c ft_lstnew.c ft_lstmap.c ft_lstlast.c ft_lstiter.c \
			ft_lstdelone.c ft_lstclear.c ft_lstadd_front.c ft_lstadd_back.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)

NAME = libft.a
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

bonus: $(OBJ) $(BONUS_OBJ)
	$(AR) $(NAME) $(OBJ) $(BONUS_OBJ)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
