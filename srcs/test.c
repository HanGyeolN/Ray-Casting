#include "raycasting.h"

int		main(void)
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