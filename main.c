#include <unistd.h>
#include "mlx.h"

typedef struct	s_window
{
	int		width;
	int		height;
	void	*win_ptr;
	void	*mlx_ptr;
}				t_window;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		deal_key(int key, void *param)
{
	ft_putchar('X');
	return (0);
}

int		render(void *mlx_ptr, void *win_ptr)
{
	int		r;
	int		c;

	c = 10;
	while (++c < 490)
	{
		r = 10;
		while (++r < 490)
			mlx_pixel_put(mlx_ptr, win_ptr, r, c, 0xFFFFFF);
	}
	return (0);
}

void	init_window(t_window *window, int width, int height, char *title)
{
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	window->width = width;
	window->height = height;
}

int		main(void)
{
	t_window	*window;

	if (!(window = malloc(sizeof(t_window))))
		return (0);
	init_window(window, 360, 200, "title_test");
	mlx_key_hook(window->win_ptr, deal_key, (void *)0);
	mlx_loop(window->mlx_ptr);
}
