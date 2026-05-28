NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror
INCLUDES := -Iincludes

SRCS := src/main.c src/loop.c ./src/lexer/lexer_split.c ./src/lexer/lexer_split1.c \
		./src/lexer/lexer_split1_utils.c \
		./libft/ft_toupper.c ./libft/ft_tolower.c ./libft/ft_substr.c ./libft/ft_strtrim.c \
		./libft/ft_strrchr.c ./libft/ft_strnstr.c ./libft/ft_strncmp.c ./libft/ft_strmapi.c \
		./libft/ft_strlen.c ./libft/ft_strlcpy.c ./libft/ft_strlcat.c ./libft/ft_strjoin.c\
		./libft/ft_striteri.c ./libft/ft_strdup.c ./libft/ft_strchr.c ./libft/ft_split.c \
		./libft/ft_putstr_fd.c ./libft/ft_putnbr_fd.c ./libft/ft_putendl_fd.c ./libft/ft_putchar_fd.c \
	  ./libft/ft_memset.c ./libft/ft_memcpy.c ./libft/ft_memcmp.c ./libft/ft_memchr.c \
	  ./libft/ft_memmove.c ./libft/ft_itoa.c ./libft/ft_isprint.c ./libft/ft_isdigit.c \
	  ./libft/ft_isascii.c ./libft/ft_isalpha.c ./libft/ft_isalnum.c \
	  ./libft/ft_calloc.c ./libft/ft_bzero.c ./libft/ft_atoi.c ./libft/ft_strcmp.c \
	  ./src/env/env_clear.c ./src/env/env_get.c ./src/env/env_init.c ./src/env/env_print.c \
	  ./src/env/env_set.c ./src/env/env_to_envp_helper.c ./src/env/env_to_envp.c \
	  ./src/env/env_unset.c ./src/parser/parser.c ./src/parser/parser_print.c \
	  ./src/executor/exec_external.c ./src/executor/exec_one.c ./src/executor/path_resolve.c \
	  ./src/exec/apply_redir.c ./src/exec_pipeline/execute.c ./src/maintest.c \
	  ./src/builtins/echo.c ./src/exec/stdio_backup.c ./src/builtins/cd.c ./src/builtins/pwd.c \
	  ./src/builtins/env.c ./src/exec_pipeline/execute1.c ./src/exec_pipeline/execute2.c \
	  ./src/exec_pipeline/execute3.c ./src/executor/path_resolve_helper.c \
	  ./src/lexer/lexer_split2.c ./src/lexer/lexer_split2_utils.c ./src/lexer/lexer_split3.c ./src/lexer/lexer_split4.c \
	  ./src/lexer/lexer_split5.c ./src/lexer/lexer_split6.c ./src/lexer/lexer_split_ifs.c ./src/lexer/lexer_split_ifs_utils.c \
	  ./src/parser/parser2.c \
	  ./src/parser/parser3.c ./src/parser/parser4.c ./src/parser/parser5.c ./src/lexer/lexer_split7.c \
	  ./src/parser/parser6.c ./src/utils.c ./src/builtins/unset.c ./src/builtins/export.c \
	  ./src/builtins/export_helper.c\
	  ./src/signals/signals.c ./src/signals/signals2.c ./src/builtins/export_print.c \
	  ./src/builtins/exit.c ./src/builtins/exit_helper.c ./src/lexer/lexer_split8.c\
	  ./src/heredoc/heredoc_read.c ./src/heredoc/heredoc_expand.c

OBJS := $(SRCS:.c=.o)

# On many Linux setups you also need -lncurses (or -ltinfo).
READLINE_LIBS := -lreadline -lhistory -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE_LIBS) -o $(NAME)

%.o: %.c includes/minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
