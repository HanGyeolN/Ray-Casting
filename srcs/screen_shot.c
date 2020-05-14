#include <stdio.h>
#include "raycasting.h"

#define	BYTES_PER_PIXEL 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

// init_bitmap_file_header(t_bitmap_file_header *bfh)
// {
	
// }

// void			init_bitmap(t_bitmap *bitmap)
// {
// 	init_bitmap_file_header(&(bitmap->file_header));
// 	init_bitmap_info_header(&(bitmap->info_header));
// }

// int				screen_shot(t_scene *scene){
// 	t_bitmap	bitmap;
// 	int			height;
// 	int			width;

// 	height = (int)scene->window.height;
// 	width = (int)scene->window.width;
// 	init_bitmap(&bitmap, height, width, padding_size);

// 	int	color;
// 	int	r,g,b;
// 	unsigned char image[height][width][BYTES_PER_PIXEL];
// 	char* imageFileName = "bitmapImage.bmp";
// 	int i, j;

// 	for(i=0; i<height; i++){
// 		for(j=0; j<width; j++){
// 			color = scene->window.img_data[i * width + j];
// 			r = color >> 16;
// 			g = (color - (r << 16)) >> 8;
// 			b = (color - (r << 16) - (g << 8));
// 			image[i][j][2] = (unsigned char)r;
// 			image[i][j][1] = (unsigned char)g;
// 			image[i][j][0] = (unsigned char)b;
// 		}
// 	}
// 	generateBitmapImage((unsigned char *)image, height, width, imageFileName);
// 	printf("image saved\n");
// 	return (0);
// }

t_bitmap_file_header	*create_bitmap_file_header(int height, int width, int padding_size)
{
	int file_size;
	t_bitmap_file_header	*bfh;

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (BYTES_PER_PIXEL * width + padding_size) * height;
	bfh = malloc(sizeof(t_bitmap_file_header));
	ft_memset(bfh, 0, sizeof(t_bitmap_file_header));
	bfh->bf_type[0] = (unsigned char)('B');
	bfh->bf_type[1] = (unsigned char)('M');
	bfh->bf_size[0] = (unsigned char)(file_size);
	bfh->bf_size[1] = (unsigned char)(file_size >> 8);
	bfh->bf_size[2] = (unsigned char)(file_size >> 16);
	bfh->bf_size[3] = (unsigned char)(file_size >> 24);
	bfh->bf_off_bits[0] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	return (bfh);
}

unsigned char	*createBitmapInfoHeader(int height, int width){
	unsigned char *info_header;

	if (!(info_header = malloc(sizeof(unsigned char) * 40)))
		return (0);
	ft_memset(info_header, 0, 40);
	info_header[ 0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[ 4] = (unsigned char)(width);
	info_header[ 5] = (unsigned char)(width >> 8);
	info_header[ 6] = (unsigned char)(width >> 16);
	info_header[ 7] = (unsigned char)(width >> 24);
	info_header[ 8] = (unsigned char)(height);
	info_header[ 9] = (unsigned char)(height >> 8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(BYTES_PER_PIXEL * 8);
	return info_header;
}

void			generateBitmapImage(unsigned char *image, int height, int width, char* imageFileName)
{
	int 			padding_size;
	int				fd;
	unsigned char	*file_header;
	unsigned char	*info_header;
	t_bitmap_file_header	*file_s_header;

	padding_size = (4 - (width * BYTES_PER_PIXEL) % 4) % 4;
	fd = open(imageFileName, O_WRONLY | O_CREAT, 0777);
	file_s_header = create_bitmap_file_header(height, width, padding_size);
	info_header = createBitmapInfoHeader(height, width);
	write(fd, file_s_header, FILE_HEADER_SIZE);
	write(fd, info_header, INFO_HEADER_SIZE);
	int i, j;
	write(fd, image, BYTES_PER_PIXEL * width);
	for(i=0; i<height; i++){
		j = 0;
		write(fd, image + (i * width * BYTES_PER_PIXEL), BYTES_PER_PIXEL * width);
	}
	free(file_s_header);
	free(info_header);
	close(fd);
}

int				screen_shot(t_scene *scene){
	int	color;
	int height;
	int width;

	height = (int)scene->window.height;
	width = (int)scene->window.width;
	unsigned char image[height][width][BYTES_PER_PIXEL];
	// make_image();
	int		i;
	int		j;
	i = 0;
	j = 0;
	int	r,g,b;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			color = scene->window.img_data[i * width + j];
			// put_color_to_image(&image);
			r = color >> 16;
			g = (color - (r << 16)) >> 8;
			b = (color - (r << 16) - (g << 8));
			image[i][j][2] = (unsigned char)r;
			image[i][j][1] = (unsigned char)g;
			image[i][j][0] = (unsigned char)b;
			j++;
		}
		i++;
	}
	generateBitmapImage((unsigned char *)image, height, width, "bitmapImage.bmp");
	return (0);
}