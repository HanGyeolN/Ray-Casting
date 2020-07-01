/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:19:18 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:32:39 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void		put_color_to_image(unsigned char *image, int color, int idx)
{
	int		r;
	int		g;
	int		b;

	r = color >> 16;
	g = (color - (r << 16)) >> 8;
	b = (color - (r << 16) - (g << 8));
	image[idx + 2] = (unsigned char)r;
	image[idx + 1] = (unsigned char)g;
	image[idx] = (unsigned char)b;
}

t_bmp_fh	*create_bitmap_file_header(int height, int width, int padding_size)
{
	int			file_size;
	t_bmp_fh	*bfh;

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + \
				(BYTES_PER_PIXEL * width + padding_size) * height;
	if (!(bfh = malloc(sizeof(t_bmp_fh))))
		return (0);
	ft_memset(bfh, 0, sizeof(t_bmp_fh));
	bfh->bf_type[0] = (unsigned char)('B');
	bfh->bf_type[1] = (unsigned char)('M');
	bfh->bf_size[0] = (unsigned char)(file_size);
	bfh->bf_size[1] = (unsigned char)(file_size >> 8);
	bfh->bf_size[2] = (unsigned char)(file_size >> 16);
	bfh->bf_size[3] = (unsigned char)(file_size >> 24);
	bfh->bf_off_bits[0] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	return (bfh);
}

t_bmp_ih	*create_bitmap_info_header(int height, int width)
{
	t_bmp_ih	*bih;

	if (!(bih = malloc(sizeof(t_bmp_ih))))
		return (0);
	ft_memset(bih, 0, sizeof(t_bmp_ih));
	bih->bi_size[0] = (unsigned char)(INFO_HEADER_SIZE);
	bih->bi_width[0] = (unsigned char)(width);
	bih->bi_width[1] = (unsigned char)(width >> 8);
	bih->bi_width[2] = (unsigned char)(width >> 16);
	bih->bi_width[3] = (unsigned char)(width >> 24);
	bih->bi_height[0] = (unsigned char)(height);
	bih->bi_height[1] = (unsigned char)(height >> 8);
	bih->bi_height[2] = (unsigned char)(height >> 16);
	bih->bi_height[3] = (unsigned char)(height >> 24);
	bih->bi_planes[0] = (unsigned char)(1);
	bih->bi_bit_count[0] = (unsigned char)(BYTES_PER_PIXEL * 8);
	return (bih);
}

void		generate_bitmap_image(unsigned char *image, int height, int width)
{
	int			padding_size;
	int			fd;
	t_bmp_fh	*file_s_header;
	t_bmp_ih	*info_s_header;

	padding_size = (4 - (width * BYTES_PER_PIXEL) % 4) % 4;
	fd = open("bitmapImage.bmp", O_WRONLY | O_CREAT, 0777);
	file_s_header = create_bitmap_file_header(height, width, padding_size);
	info_s_header = create_bitmap_info_header(height, width);
	write(fd, file_s_header, FILE_HEADER_SIZE);
	write(fd, info_s_header, INFO_HEADER_SIZE);
	write(fd, image, height * width * BYTES_PER_PIXEL);
	free(file_s_header);
	free(info_s_header);
	close(fd);
}

int			image_to_bmp(int height, int width, int *img_data)
{
	int				i;
	int				j;
	int				idx;
	unsigned char	*image;

	if (!(image = malloc(sizeof(char) * (height * width * BYTES_PER_PIXEL))))
		return (0);
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			idx = i * width * BYTES_PER_PIXEL + j * BYTES_PER_PIXEL;
			put_color_to_image(image, img_data[i * width + j], idx);
		}
	}
	generate_bitmap_image(image, height, width);
	free(image);
	return (0);
}
