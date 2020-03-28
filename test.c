#include "raycasting.h"

int		main(void)
{
	int		i;
	int		bpx, sl, en;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*img_data;

	i = 0;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "test");
	img_ptr = mlx_new_image(mlx_ptr, 1000, 1000);
	img_data = (int *)mlx_get_data_addr(img_ptr, &bpx, &sl, &en);
	while (++i < 505000)
	{
		img_data[i] = 0xFFFFFF;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

	// img_ptr = mlx_png_file_to_image(mlx_ptr, "./Image001.png", &i, &j);
	/*
	while (i < 1000)
	{
		j = 0;
		while (j < 1000)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	*/
	// mlx_string_put(mlx_ptr, win_ptr, 100, 100, 0xFFFFFF, "hello world\n");
	
	mlx_loop(mlx_ptr);
	return (0);
}