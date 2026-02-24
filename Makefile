NAME		= fdf
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -I$(LIBFT_DIR)
MLXFLAGS = -lmlx -lXext -lX11
LDFLAGS = -L$(LIBFT_DIR) -lft
SRCS = fdf.c read_parse.c setup.c utils.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

debug: fclean
	$(MAKE) -C $(LIBFT_DIR) debug
	$(MAKE) all CFLAGS="$(CFLAGS) -g"
.PHONY: all clean fclean re debug

-include $(DEPS)