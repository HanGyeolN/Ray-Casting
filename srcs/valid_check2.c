#include "raycasting.h"

/*
** check color
** valid color range : 0 to 255
*/

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

int		is_valid_horizontal(t_cub *cub)
{
	int		r;
	int		c;
	int		right;
	int		check;

	r = 0;
	check = 0;
	
	while (r < cub->map_h)
	{
		c = 0;
		while (c < cub->map_w)
		{
			if (cub->map[r][c] == '1')
			{
				check = 0;
				right = cub->map_w - 1;
				while (right > c)
				{
					if (cub->map[r][right] == '1')
					{
						check = 1;
						break;
					}
					else if (cub->map[r][right] != '1' && cub->map[r][right] != ' ')
						return (0);
					right--;
				}
				if (check == 1)
					break;
				else
					return (0);
			}
			c++;
		}
		r++;
	}
	return (1);
}

int		is_valid_vertical(t_cub *cub)
{
	int		r;
	int		c;
	int		bottom;
	int		check;

	c = 0;
	check = 0;
	while (c < cub->map_w)
	{
		r = 0;
		while (r < cub->map_h)
		{
			if (cub->map[r][c] == '1')
			{
				check = 0;
				bottom = cub->map_h - 1;
				while (bottom > r)
				{
					if (cub->map[bottom][c] == '1')
					{
						check = 1;
						break;
					}
					else if (cub->map[bottom][c] != '1' && cub->map[bottom][c] != ' ')
						return (0);
					bottom--;
				}
				if (check == 1)
					break;
				else
					return (0);
			}
			r++;
		}
		c++;
	}
	return (1);
}

int		is_valid_map(t_cub *cub)
{
	if (!(is_valid_vertical(cub)) || !(is_valid_horizontal(cub)))
		return (0);
	return (1);
}