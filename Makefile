CC = gcc
NAME = cub3D
CFLAGS = -Wall -Werror -Wextra
SRC = main.c			render.c			init.c			close_game.c	\
	  parse_scene.c		raycast.c			event.c			screen_shot.c	\
	  player_move.c		player_rotate.c		init_sprite.c	init_texture.c	\
	  parse_map.c		parse_resolution.c	load_scene.c	convert_map.c	\
	  valid_check.c		valid_check2.c		parse_utils.c	parse_color.c	\
	  cast_wall.c		cast_sprite.c	sprite_utils.c					\
	  valid_check3.c	cast_wall_texture.c	cast_wall_utils.c				\

SRC_DIR = srcs
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(SRCS:%.c=%.o)
HEADERS = includes

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(HEADERS) \
		-L ./ -lmlx -lft -framework OpenGL -framework AppKit -lz

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^ -I $(HEADERS)

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
