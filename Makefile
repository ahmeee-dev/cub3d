NAME		= cub3d

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
MLX_FLAGS	= -framework OpenGL -framework AppKit

CDIR		= src/
RND_DIR		= rendering/
HDIR		= includes
LIBFTDIR	= libft
MLXDIR		= .minilibx/minilibx_opengl_20191021

CFILES		= main.c $(addprefix $(RND_DIR), map.c mymlx.c mymlx_utils.c raycasting.c raycasting_utils.c)
SRCS		= $(addprefix $(CDIR), $(CFILES))
OBJS		= $(SRCS:%.c=%.o)

MLXLIB		= $(MLXDIR)/libmlx.a
LIBFTLIB	= libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(MLXLIB) $(LIBFTLIB)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $^ -o $@

$(MLXLIB):
	$(MAKE) -C $(MLXDIR)

$(LIBFTLIB):
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c $(HDIR)/*
	$(CC) $(CFLAGS) -I $(HDIR) -I $(LIBFTDIR)/includes -I $(MLXDIR) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean_mlx:
	$(MAKE) clean -C $(MLXDIR)

fclean_libft:
	$(MAKE) fclean -C $(LIBFTDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
