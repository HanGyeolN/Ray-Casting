#include "raycasting.h"
#include "libftprintf.h"

/*
int		test_mlx(void)
{
	int		i, j;
	int		bpx, sl, en, w, h;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*t_ptr;
	int		*t_data;
	void	*img_ptr;
	int		*img_data;
	int		(*arr2)[200];

	i = 0;
	j = 0;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "test");
	img_ptr = mlx_new_image(mlx_ptr, 500, 500);
	img_data = (int *)mlx_get_data_addr(img_ptr, &bpx, &sl, &en);
	t_ptr = mlx_png_file_to_image(mlx_ptr, "./textures/wall_s.png", &w, &h);
	t_data = (int *)mlx_get_data_addr(t_ptr, &bpx, &sl, &en);
	arr2 = (int(*)[200])t_data;
	while (j < 500)
	{
		i = 100;
		while (i < 400)
		{
			img_data[500 * j + i] = arr2[(int)((2 / 5.0) * j)][(int)((2 / 3.0) * (i - 100))];
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
*/

#include <stdio.h>
#include <string.h>

/*
** Maximum path length : 200
*/

typedef struct	s_cub
{
	int		res_w;
	int		res_h;
	char	tex_n[200];
	char	tex_s[200];
	char	tex_w[200];
	char	tex_e[200];
	char	tex_i[200];
	int		color_f;
	int		color_c;
}				t_cub;

int		split_len(char **splits)
{
	int		len;

	len = 0;
	while (splits[len])
		len++;
	return (len);
}

void	free_splits(char **splits)
{
	int		i;

	i = 0;
	while (splits[i])
	{
		free(splits[i]);
		i++;
	}
	free(splits);
}

int		parse_resolution(char *line, t_cub *cub)
{
	char	**splits;
	int		i;
	int		idx;
	int		len;

	splits = ft_split(line, ' ');
	if (split_len(splits) != 3)
		return (0);
	idx = 1;
	while (idx < 3)
	{
		i = -1;
		len = ft_strlen(splits[idx]);
		while (++i < len)
			if (is_numeric(splits[idx][i]) == 0)
				return (0);
		if (idx == 1)
			cub->res_w = ft_atoi(splits[idx]);
		else
			cub->res_h = ft_atoi(splits[idx]);
		idx++;
	}
	free_splits(splits);
	return (1);
}

void	print_cub(t_cub *cub)
{
	ft_printf("Resolution Width: %d\n", cub->res_w);
	ft_printf("Resolution Height: %d\n", cub->res_h);
	ft_printf("Texture North: %s\n", cub->tex_n);
	ft_printf("Texture South: %s\n", cub->tex_s);
	ft_printf("Texture West: %s\n", cub->tex_w);
	ft_printf("Texture East: %s\n", cub->tex_e);
	ft_printf("Texture Item: %s\n", cub->tex_i);
	ft_printf("Floor Color: %x\n", cub->color_f);
	ft_printf("Ceiling Color: %x\n", cub->color_c);
}

int		parse_path(char *line, t_cub *cub)
{
	char	**splits;

	splits = ft_split(line, ' ');
	if (split_len(splits) != 2)
		return (0);
	if (ft_strcmp(splits[0], "NO") == 0)
		ft_strcpy(cub->tex_n, splits[1]);
	else if (ft_strcmp(splits[0], "SO") == 0)
		ft_strcpy(cub->tex_s, splits[1]);
	else if (ft_strcmp(splits[0], "WE") == 0)
		ft_strcpy(cub->tex_w, splits[1]);
	else if (ft_strcmp(splits[0], "EA") == 0)
		ft_strcpy(cub->tex_e, splits[1]);
	else if (ft_strcmp(splits[0], "S") == 0)
		ft_strcpy(cub->tex_i, splits[1]);
	free_splits(splits);
	return (1);
}

int		is_valid_color(char **colors)
{
	int		idx;
	int		i;
	idx = 0;
	i = -1;
	while (idx < 3)
	{
		while (++i < ft_strlen(colors[idx]))
			if (is_numeric(colors[idx][i]) == 0)
				return (0);
		if (ft_atoi(colors[idx]) < 0 || ft_atoi(colors[idx]) > 255)
			return (0);
		idx++;
	}
	return (1);
}

int		parse_color(char *line, t_cub *cub)
{
	char	**splits;
	char	**colors;
	int		color;

	splits = ft_split(line, ' ');
	if (split_len(splits) != 2)
		return (0);
	colors = ft_split(splits[1], ',');
	if (split_len(colors) != 3 || !(is_valid_color(colors)))
		return (0);
	color = 0;
	color += 16 * 16 * 16 * 16 * ft_atoi(colors[0]);
	color += 16 * 16 * ft_atoi(colors[1]);
	color += ft_atoi(colors[2]);
	if (splits[0][0] == 'F')
		cub->color_f = color;
	else if (splits[0][0] == 'C')
		cub->color_c = color;
	free_splits(splits);
	free_splits(colors);
	return (1);
}

int		is_texture(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 ||
			ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 ||
			ft_strncmp(line, "EA ", 3) == 0 ||
			ft_strncmp(line, "S ", 2) == 0)
		return (1);
	return (0);
}

int		test_split(void)
{
	int		i;
	int		fd;
	int		check;
	char	*line;
	char	*find;
	char	**splits;
	int		n_split;
	int		cmp;
	int		len;
	t_cub	cub;
	int		idx;

	check = 0b00000000;
	fd = open("test.cub", O_RDONLY);
	if (fd < 0)
		perror("[scene open]");
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "R ", 2) == 0)
		{
			if (!(parse_resolution(line, &cub)))
			{
				ft_printf("parse error\n");
				return (0);
			}
		}
		else if (is_texture(line))
		{
			if (!(parse_path(line, &cub)))
			{
				ft_printf("parse error\n");
				return (0);
			}
		}
		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0 )
		{
			if (!(parse_color(line, &cub)))
			{
				ft_printf("parse error\n");
				return (0);
			}
		}
	}
	close(fd);
	print_cub(&cub);
	return (0);
}

int		test_strstr(void)
{
	char	*find;

	find = ft_strstr("R", "R");
	if (find != 0)
		ft_printf("%s\n", find);
	return (0);
}

int		main(void)
{
	test_split();
	return (0);
}

int		test_binary(void)
{
	int		a;
	int		b;
	int		c;

	a = 0b00010000;
	b = 0b01000100;
	c = a | b;
	ft_printf("%d\n", c);
	return (0);
}