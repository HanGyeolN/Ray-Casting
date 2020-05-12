CC = gcc
NAME = cub3D
CFLAGS = -Wall -Werror -Wextra
SRC = main.c	render.c	init.c	\
	  parse_scene.c	ray.c	event.c		screen_shot.c

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


