/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 10:50:47 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/28 13:38:56 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->buffer + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

float	dist(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ray_draw(t_all *all, float rayx, float rayy, int color)
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;

	x1 = all->pos.px;
	y1 = all->pos.py;
	x2 = rayx;
	y2 = rayy;
	while (x1 <= x2)
	{
		my_mlx_pixel_put(&all->img, x1, y1, color);
		x1 += 0.1;
		y1 = (x1 - all->pos.px) / (x2 - all->pos.px) * (y2 - all->pos.py) + all->pos.py;
	}
	while (x1 > x2)
	{
		my_mlx_pixel_put(&all->img, x1, y1, color);
		x1 -= 0.1;
		y1 = (x1 - all->pos.px) / (x2 - all->pos.px) * (y2 - all->pos.py) + all->pos.py;
	}
}


void	rays3D_draw(t_all *all, int color)
{
	t_ray rays;

	rays.a = all->pos.pa - 30 * M_PI / 180;
	if (rays.a < 0)
		rays.a += 2 * M_PI;
	if (rays.a > 2 * M_PI)
		rays.a -= 2 * M_PI;
	rays.r = 0;
	while (rays.r < 60)
	{
		// Check horizontals
		rays.dof = 0;
		rays.dish = 1000000;
		rays.hx = all->pos.px;
		rays.hy = all->pos.py;
		rays.tan = -1 / tan(rays.a);
		if (rays.a > M_PI)
		{
			rays.y = (((int)all->pos.py >> 6) << 6) - 0.0001;
			rays.x = (all->pos.py - rays.y) * rays.tan + all->pos.px;
			rays.yo = -64;
			rays.xo = rays.yo * rays.tan * -1;
		}	
		if (rays.a < M_PI)
		{
			rays.y = (((int)all->pos.py >> 6) << 6) + 64;
			rays.x = (all->pos.py - rays.y) * rays.tan + all->pos.px;
			rays.yo = 64;
			rays.xo = rays.yo * rays.tan * -1;
		}
		if (rays.a == 0 || rays.a == M_PI)
		{
			rays.x = all->pos.px;
			rays.y = all->pos.py;
			rays.dof = 8;
		}
		while (rays.dof < 8)
		{
			rays.mx = (int)(rays.x) >> 6; 
			rays.my = (int)(rays.y) >> 6;
			rays.mp = rays.my * all->maze.x + rays.mx;
			if (rays.mp > 0 && rays.mp < all->maze.x * all->maze.y 
					&& all->maze.map[rays.mp] == 1)
			{
				rays.hx = rays.x;
				rays.hy = rays.y;
				rays.dish = dist(all->pos.px, all->pos.py, rays.hx, rays.hy);
				rays.dof = 8;
			}
			else
			{
				rays.x += rays.xo;
				rays.y += rays.yo;
				rays.dof++;
			}
		}
	//	rays.r++;
	//	if (rays.x < 1024 && rays.x > 0 && rays.y > 0 && rays.y < 512)
	//		ray_draw(all, rays.x, rays.y, color);
		// Check verticals
		rays.dof = 0;
		rays.disv = 1000000;
		rays.vx = all->pos.px;
		rays.vy = all->pos.py;
		rays.ntan = tan(rays.a) * -1;
		if (rays.a > M_PI_2 && rays.a < M_PI_2 * 3)
		{
			rays.x = (((int)all->pos.px >> 6) << 6) - 0.0001;
			rays.y = (all->pos.px - rays.x) * rays.ntan + all->pos.py;
			rays.xo = -64;
			rays.yo = rays.xo * rays.ntan * -1;
		}	
		if (rays.a < M_PI_2 || rays.a > M_PI_2 * 3)
		{
			rays.x = (((int)all->pos.px >> 6) << 6) + 64;
			rays.y = (all->pos.px - rays.x) * rays.ntan + all->pos.py;
			rays.xo = 64;
			rays.yo = rays.xo * rays.ntan * -1;
		}
		if (rays.a == 0 || rays.a == M_PI)
		{
			rays.x = all->pos.px;
			rays.y = all->pos.py;
			rays.dof = 8;
		}
		while (rays.dof < 8)
		{
			rays.mx = (int)(rays.x) >> 6; 
			rays.my = (int)(rays.y) >> 6;
			rays.mp = rays.my * all->maze.x + rays.mx;
			if (rays.mp > 0 && rays.mp < all->maze.x * all->maze.y 
					&& all->maze.map[rays.mp] == 1)
			{
				rays.vx = rays.x;
				rays.vy = rays.y;
				rays.disv = dist(all->pos.px, all->pos.py, rays.vx, rays.vy);
				rays.dof = 8;
			}
			else
			{
				rays.x += rays.xo;
				rays.y += rays.yo;
				rays.dof++;
			}
		}
		rays.r++;
		if (rays.disv < rays.dish)
		{
			rays.x = rays.vx;
			rays.y = rays.vy;
			rays.dist = rays.disv;
		}
		if (rays.dish < rays.disv)
		{
			rays.x = rays.hx;
			rays.y = rays.hy;
			rays.dist = rays.dish;
		}
		if (rays.x < 1024 && rays.x > 0 && rays.y > 0 && rays.y < 512)
			ray_draw(all, rays.x, rays.y, color);

		// Draw 3D walls
		rays.lineh = (all->maze.size * 320) / rays.dist;
		if (rays.lineh > 320)
			rays.lineh = 320;
		rays.lineo = 160 - rays.lineh / 2;

		rays.a += 1 * M_PI / 180;
		if (rays.a < 0)
			rays.a += 2 * M_PI;
		if (rays.a > 2 * M_PI)
			rays.a -= 2 * M_PI;
	}
}

void	player_draw(t_all *all, int color)
{
	int		size;
	float	round_x;
	float	round_y;

	size = 5;
	round_y = all->pos.py - size;
	while (round_y < all->pos.py + size)
	{
		round_x = all->pos.px - size;
		while (round_x < all->pos.px + size)
		{
			my_mlx_pixel_put(&all->img, round_x, round_y, color);
			round_x++;
		}
		round_y++;
	}
}

void	vision_line_draw(t_all *all, int color)
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;

	x1 = all->pos.px;
	y1 = all->pos.py;
	x2 = all->pos.px + all->pos.pdx * 5;
	y2 = all->pos.py + all->pos.pdy * 5;
	while (x1 <= x2)
	{
		my_mlx_pixel_put(&all->img, x1, y1, color);
		x1 += 0.1;
		y1 = (x1 - all->pos.px) / (x2 - all->pos.px) * (y2 - all->pos.py) + all->pos.py;
	}
	while (x1 > x2)
	{
		my_mlx_pixel_put(&all->img, x1, y1, color);
		x1 -= 0.1;
		y1 = (x1 - all->pos.px) / (x2 - all->pos.px) * (y2 - all->pos.py) + all->pos.py;
	}
}

void	map2D_draw(t_all *all)
{
	int	x;
	int	y;
	int	xo;
	int	yo;
	int	size_x;
	int	size_y;

	y = 0;
	size_y = 0;
	while (y < all->maze.y)
	{
		size_x = 0;
		x = 0;
		while (x < all->maze.x)
		{
			yo = 0;
			while (yo + 1 < all->maze.size)
			{
				xo = 0;
				while (xo < all->maze.size - 1)
				{
					if (all->maze.map[y * all->maze.x + x] == 1)
						my_mlx_pixel_put(&all->img, xo + size_x, yo + size_y, 0xFFFFFF);
					else
						my_mlx_pixel_put(&all->img, xo + size_x, yo + size_y, 0x8E8E8E);
					xo++;
				}
				yo++;
			}
			size_x += all->maze.size;
			x++;
		}
		size_y += all->maze.size;
		y++;
	}
}

int		moving_player(t_all *all)
{
	map2D_draw(all);
	player_draw(all, 0xFFFF00);
	vision_line_draw(all, 0xFFFF00);
	rays3D_draw(all, 0x00FF00);
	mlx_put_image_to_window(all->mlx.mlx_ptr, all->win.win_ptr, all->img.img_ptr, 0, 0);
	return (1);
}

int		key_press(int keycode, t_all *all)
{
	player_draw(all, 0x0);
	vision_line_draw(all, 0x0);
	rays3D_draw(all, 0x0);
	if (keycode == KEY_W)
	{
		all->pos.px += all->pos.pdx * all->draw.ray.speed;
		all->pos.py += all->pos.pdy * all->draw.ray.speed;
	}
	if (keycode == KEY_A)
	{
		all->pos.pa -= 0.1;
		if (all->pos.pa < 0)
			all->pos.pa += 2 * M_PI;
		all->pos.pdx = cos(all->pos.pa) * all->draw.ray.size;
		all->pos.pdy = sin(all->pos.pa) * all->draw.ray.size;
	}
	if (keycode == KEY_S)
	{
		all->pos.px -= all->pos.pdx * all->draw.ray.speed;
		all->pos.py -= all->pos.pdy * all->draw.ray.speed;
	}
	if (keycode == KEY_D)
	{
		all->pos.pa += 0.1;
		if (all->pos.pa > 2 * M_PI)
			all->pos.pa -= 2 * M_PI;
		all->pos.pdx = cos(all->pos.pa) * all->draw.ray.size;
		all->pos.pdy = sin(all->pos.pa) * all->draw.ray.size;
	}
	if (keycode == KEY_ESC)
	{
		system("leaks cub3D");
		exit(EXIT_SUCCESS);
	}
	return (1);
}

void	init(t_all *all)
{
	all->pos.px = 256;
	all->pos.py = 256;
	all->pos.pa = 0;
	all->draw.ray.size = 5;
	all->draw.ray.speed = 3;
	all->pos.fova = 66 * (M_PI / 180);
	all->pos.raya = all->pos.pa - (all->pos.fova / 2);
	all->pos.pdx = cos(all->pos.pa) * all->draw.ray.size;
	all->pos.pdy = sin(all->pos.pa) * all->draw.ray.size;
	all->maze.x = 8;
	all->maze.y = 8;
	all->maze.size = 64;
	int map[64] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 1, 0, 1,
		1, 0, 1, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1
	};
	int i = 0;
	while (i < 64)
	{
		all->maze.map[i] = map[i];
		i++;
	}
	all->maze.map[i] = '\0';
}

int		main()
{
	t_all	all;

	init(&all);
	all.mlx.mlx_ptr = mlx_init();
	all.win.win_ptr = mlx_new_window(all.mlx.mlx_ptr, 1024, 512, "cub3D");
	all.img.img_ptr = mlx_new_image(all.mlx.mlx_ptr, 1024, 512);
	all.img.buffer = mlx_get_data_addr(all.img.img_ptr, &all.img.bits_per_pixel, &all.img.size_line, &all.img.endian);
	mlx_hook(all.win.win_ptr, 2, 0, &key_press, &all);
	mlx_loop_hook(all.mlx.mlx_ptr, &moving_player, &all);
	mlx_loop(all.mlx.mlx_ptr);
	return (1);
}
