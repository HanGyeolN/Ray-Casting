/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:04:08 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:13:01 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int		xpm_to_image(void **image, void *mlx, char *filepath)
{
	int		tp;

	if (!(*image = mlx_xpm_file_to_image(mlx, filepath, &tp, &tp)))
	{
		error("no such file | ");
		ft_printf(filepath);
		return (0);
	}
	return (1);
}

void	init_texture_data(t_texture *t)
{
	int		tp;

	t->n_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->n, &tp, &tp, &tp);
	t->s_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->s, &tp, &tp, &tp);
	t->w_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->w, &tp, &tp, &tp);
	t->e_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->e, &tp, &tp, &tp);
	t->i_data = (int(*)[SPRITE_W])mlx_get_data_addr(t->i, &tp, &tp, &tp);
	t->f_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->f, &tp, &tp, &tp);
	t->c_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->c, &tp, &tp, &tp);
}

int		init_texture(void *mlx_ptr, t_texture *tex, t_cub *cub)
{
	if (!(xpm_to_image(&(tex->n), mlx_ptr, cub->tex_n)))
		return (0);
	if (!(xpm_to_image(&(tex->s), mlx_ptr, cub->tex_s)))
		return (0);
	if (!(xpm_to_image(&(tex->w), mlx_ptr, cub->tex_w)))
		return (0);
	if (!(xpm_to_image(&(tex->e), mlx_ptr, cub->tex_e)))
		return (0);
	if (!(xpm_to_image(&(tex->i), mlx_ptr, cub->tex_i)))
		return (0);
	if (!(xpm_to_image(&(tex->f), mlx_ptr, "./textures/floor.xpm")))
		return (0);
	if (!(xpm_to_image(&(tex->c), mlx_ptr, "./textures/ceiling.xpm")))
		return (0);
	init_texture_data(tex);
	return (1);
}
