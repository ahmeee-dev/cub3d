NAME			= cub3d
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

SRC_DIR			= src/
RND_DIR			= rendering/
PRS_DIR			= parsing/
H_DIR			= includes
LIBFT_DIR		= libft
MLX_DIR			= .minilibx/minilibx-linux

C_FILES			= main.c
RND_FILES		= raycaster.c raycaster_utils.c mymlx.c mymlx_utils.c fps.c
PRS_FILES		= map_save.c gfx_save.c matrix.c parsing.c general_utils.c map_utils.c

SRCS			= $(C_FILES) $(addprefix $(RND_DIR), $(RND_FILES)) $(addprefix $(PRS_DIR), $(PRS_FILES))
OBJS			= $(addprefix $(SRC_DIR), $(SRCS:.c=.o))

MLX_LIB			= $(MLX_DIR)/libmlx.a
LIBFT_LIB		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -L $(LIBFT_DIR) -lft

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(SRC_DIR)%.o: $(SRC_DIR)%.c $(H_DIR)/cub3d.h
	$(CC) $(CFLAGS) -I $(H_DIR) -I $(LIBFT_DIR)/includes -I $(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
