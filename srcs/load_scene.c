#include "get_next_line.h"
#include "libft.h"
#include "libftprintf.h"
#include "raycasting.h"
#include <fcntl.h>

int		load_scene(char *file_path, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if ()
	}

}