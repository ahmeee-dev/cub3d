NAME		= cub3d

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

CDIR		= src/
HDIR		= includes
LIBFTDIR	= libft
MLXDIR		= .minilibx/minilibx_opengl_20191021

CFILES		= main.c
SRCS		= $(addprefix $(CDIR), $(CFILES))
OBJS		= $(SRCS:%.c=%.o)

MLXLIB		= $(MLXDIR)/libmlx.a
LIBFTLIB	= libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(MLXLIB) $(LIBFTLIB)
	$(CC) $(CFLAGS) $^ -o $@

$(MLXLIB):
	$(MAKE) -C $(MLXDIR)

$(LIBFTLIB):
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c $(HDIR)/*
	$(CC) $(CFLAGS) -I $(HDIR) -I $(LIBFTDIR)/includes -c $< -o $@

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
