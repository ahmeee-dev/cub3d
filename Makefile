# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

NAME        = cub3d

# Compiler
CC          = gcc -fsanitize=address -g
CFLAGS      = -Wall -Wextra -Werror
MLX_FLAGS   = -framework OpenGL -framework AppKit

# Directories
CDIR        = src
HDIR        = includes
LIBFTDIR    = libft
MLXDIR      = .minilibx/minilibx_opengl_20191021

# Source files (auto-detected)
SRCS        = $(shell find $(CDIR) -name "*.c")
OBJS        = $(SRCS:.c=.o)

# Libraries
MLXLIB      = $(MLXDIR)/libmlx.a
LIBFTLIB    = $(LIBFTDIR)/libft.a

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS) $(MLXLIB) $(LIBFTLIB)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJS) $(MLXLIB) $(LIBFTLIB) -o $(NAME)

$(MLXLIB):
	$(MAKE) -C $(MLXDIR)

$(LIBFTLIB):
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HDIR) -I$(LIBFTDIR)/includes -I$(MLXDIR) -c $< -o $@

# **************************************************************************** #
#                                   CLEANUP                                    #
# **************************************************************************** #

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

fclean_mlx:
	$(MAKE) clean -C $(MLXDIR)

fclean_libft:
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re fclean_mlx fclean_libft
