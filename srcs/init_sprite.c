#include "raycasting.h"

void	count_sprite(t_map *map, t_scene *scene)
{
	int		i;
	int		j;
	int		cnt;

	cnt = 0;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->map[i][j] == '2')
				cnt++;
		}
	}
	scene->n_sprite = cnt;
}

void	set_sprite(t_map *map, t_scene *scene)
{
	int		i;
	int		j;
	int		cnt;

	i = -1;
	cnt = 0;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->map[i][j] == '2')
			{
				scene->sprite[cnt].d = 1;
				scene->sprite[cnt].y = (double)i + 0.5;
				scene->sprite[cnt].x = (double)j + 0.5;
				scene->sprite[cnt].type = map->map[i][j];
				cnt++;
			}
		}
	}
}

int		malloc_sprite(t_scene *scene)
{
	if (!(scene->z_buffer = malloc(sizeof(double) * scene->window.width)))
		return (error("malloc failed [init_sprite : scene->z_buffer]"));
	if (!(scene->sprite = malloc(sizeof(t_sprite) * scene->n_sprite)))
		return (error("malloc failed [init_sprite : scene->sprite]"));
	return (1);
}

int		init_sprite(t_map *map, t_scene *scene)
{
	count_sprite(map, scene);
	if (!(malloc_sprite(scene)))
		return (0);
	set_sprite(map, scene);
	return (1);
}