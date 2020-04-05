#include "raycasting.h"

int		deal_key(int key, void *param)
{
	int		i;
	double	temp;

	i = -1;
	param = 0;
	while (++i < N_RAY)
	{
		(player.rays[i]).color = 0x000000;
		convert_3d(window, &(player.rays[i]), i, 'd');
		ray_casting(&(player.rays[i]), map);
	}
	i = -1;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		if (key == KEY_W)
		{
			player.pos_x += cos(player.rad * PI / 180.0);
			player.pos_y += sin(player.rad * PI / 180.0);
			while (++i < N_RAY)
			{
				(player.rays[i]).pos_x = (int)player.pos_x;
				(player.rays[i]).pos_y = (int)player.pos_y;
			}
		}
		if (key == KEY_S)
		{
			player.pos_x -= cos(player.rad * PI / 180.0);
			player.pos_y -= sin(player.rad * PI / 180.0);
			while (++i < N_RAY)
			{
				(player.rays[i]).pos_x = (int)player.pos_x;
				(player.rays[i]).pos_y = (int)player.pos_y;
			}
		}
		else if (key == KEY_D)
		{
			player.pos_x -= sin((player.rad) * PI / 180.0);
			player.pos_y += cos((player.rad) * PI / 180.0);
			while (++i < N_RAY)
			{
				(player.rays[i]).pos_x = (int)player.pos_x;
				(player.rays[i]).pos_y = (int)player.pos_y;
			}
		}
		else if (key == KEY_A)
		{
			player.pos_x += sin((player.rad) * PI / 180.0);
			player.pos_y -= cos((player.rad) * PI / 180.0);
			while (++i < N_RAY)
			{
				(player.rays[i]).pos_x = (int)player.pos_x;
				(player.rays[i]).pos_y = (int)player.pos_y;
			}
		}
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		temp = (key == KEY_LEFT) ? -SPEED_ROT : SPEED_ROT;
		player.rad += temp;
		if (player.rad >= 360.0)
			player.rad -= 360.0;
		else if (player.rad < 0.0)
			player.rad += 360.0;
		while (++i < N_RAY)
		{
			(player.rays[i]).rad += temp;
			if ((player.rays[i]).rad >= 360.0)
				(player.rays[i]).rad -= 360.0;
			else if ((player.rays[i]).rad < 0.0)
				(player.rays[i]).rad += 360.0;
			if ((player.rays[i]).rad >= 89.9 && (player.rays[i]).rad <= 90.1)
				(player.rays[i]).dydx = 1;
			else if ((player.rays[i]).rad >= 269.9 && (player.rays[i]).rad <= 270.1)
				(player.rays[i]).dydx = -1;
			else
				(player.rays[i]).dydx = tan((player.rays[i]).rad * PI / 180.0);
		}
	}
	i = -1;
	while (++i < N_RAY)
	{
		(player.rays[i]).color = 0xFFFFFF;
		ray_casting(&(player.rays[i]), map);
		convert_3d(window, &(player.rays[i]), i, 'a');
	}
	render();
	return (0);
}