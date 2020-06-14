#include "raycasting.h"

int		check_right(t_cub *cub, int r, int c)
{
	int		right;

	if (cub->map[r][c] == '1')
	{
		right = cub->map_w - 1;
		while (right > c)
		{
			if (cub->map[r][right] == '1')
				return (1);
			else if (cub->map[r][right] != '1' && cub->map[r][right] != ' ')
				return (0);
			right--;
		}
	}
	return (2);
}

int		is_valid_horizontal(t_cub *cub)
{
	int		r;
	int		c;
	int		check;

	r = -1;
	while (++r < cub->map_h)
	{
		c = -1;
		while (++c < cub->map_w)
		{
			check = check_right(cub, r, c);
			if (check == 1)
				break;
			else if (check == 0)
				return (0);
		}
	}
	return (1);
}

int		check_bottom(t_cub *cub, int r, int c)
{
	int		bottom;

	if (cub->map[r][c] == '1')
	{
		bottom = cub->map_h - 1;
		while (bottom > r)
		{
			if (cub->map[bottom][c] == '1')
				return (1);
			else if (cub->map[bottom][c] != '1' && cub->map[bottom][c] != ' ')
				return (0);
			bottom--;
		}
	}
	return (2);
}

int		is_valid_vertical(t_cub *cub)
{
	int		r;
	int		c;
	int		check;

	c = -1;
	while (++c < cub->map_w)
	{
		r = -1;
		while (++r < cub->map_h)
		{
			check = check_bottom(cub, r, c);
			if (check == 1)
				break;
			else if (check == 0)
				return (0);
		}
	}
	return (1);
}

int		is_valid_character(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == '\n')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '2')
		return (1);
	return (0);
}

int		is_valid_characters(t_cub *cub)
{
	int		r;
	int		c;

	c = -1;
	while (++c < cub->map_w)
	{
		r = -1;
		while (++r < cub->map_h)
		{
			if (!(is_valid_character(cub->map[r][c])))
			{
				error("map error | not a valid character");
				ft_printf("map (%d, %d) : %c", r, c, cub->map[r][c]);
				return (0);
			}
		}
	}
	return (1);
}

int		is_valid_map(t_cub *cub)
{
	if (!(is_valid_vertical(cub)))
		return (error("map error | map must be closed"));
	if (!(is_valid_horizontal(cub)))
		return (error("map error | map must be closed"));
	if (!(is_valid_characters(cub)))
		return (0);
	return (1);
}