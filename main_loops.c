/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:08:03 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/28 13:38:09 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->buffer + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



unsigned	argb_to_color(unsigned a, unsigned r, unsigned g, unsigned b)
{
	unsigned	color;

	color = a & 0xFF;
	color <<= 8;
	color |= r & 0xFF;
	color <<= 8;
	color |= g & 0xFF;
	color <<= 8;
	color |= b & 0xFF;
	return (color);	
}

unsigned	color_to_rainbow(double frecuency, int x)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	r = sin((frecuency * x + 0) * 127 + 128);
	g = sin((frecuency * x + 2) * 127 + 128); 
	b = sin((frecuency * x + 4) * 127 + 128);
	return (argb_to_color(0, r, g, b));
}

void		draw_circle(t_img *img, int x, int y, int r, int color)
{
	double	i;
	double	angle;
	double	x1;
	double	y1;

	i = 0.1;
	while (i < 360)
	{
		angle = i;
		x1 = r * cos(angle * M_PI / 180);
		y1 = r * sin(angle * M_PI / 180);
		my_mlx_pixel_put(img, x + x1, y + y1, color);
		i += 0.1;
	}
}

int	render_moving_rainbow(t_all *all)
{
	int	x;
	int	y;

	all->img.img_ptr = mlx_new_image(all->mlx.mlx_ptr, 1920, 1080);
	all->img.buffer = mlx_get_data_addr(all->img.img_ptr, &all->img.bits_per_pixel, &all->img.size_line, &all->img.endian);
	x = 0;
	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			my_mlx_pixel_put(&all->img, x, y, (argb_to_color(0, 255, 0, 0) + x));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(all->mlx.mlx_ptr, all->mlx.win_ptr, all->img.img_ptr, 0, 0);
}

int	moving_circle(t_all *all)
{
	if (all->bol == 1)
	{
		draw_circle(&all->img, all->pos.x, all->pos.y, 100, argb_to_color(0, 255, 0, 0));
	}
	mlx_put_image_to_window(all->mlx.mlx_ptr, all->mlx.win_ptr, all->img.img_ptr, 0, 0);
}

int	key_press(int keycode, t_all *all)
{
	if (keycode == KEY_W)
	{
		all->bol = 1;
		draw_circle(&all->img, all->pos.x, all->pos.y, 100, 0x000000);
		all->pos.y -= 10;
	}
	else if (keycode == KEY_A)
	{
		all->bol = 1;
		draw_circle(&all->img, all->pos.x, all->pos.y, 100, 0x000000);
		all->pos.x -= 10;
	}
	else if (keycode == KEY_S)
	{
		all->bol = 1;
		draw_circle(&all->img, all->pos.x, all->pos.y, 100, 0x000000);
		all->pos.y += 10;
	}
	else if (keycode == KEY_D)
	{
		all->bol = 1;
		draw_circle(&all->img, all->pos.x, all->pos.y, 100, 0x000000);
		all->pos.x += 10;
	}
}

int	main()
{
	t_all	all;

	all.bol = 0;
	all.pos.x = 1920/2;
	all.pos.y = 1080/2;	
	all.mlx.mlx_ptr = mlx_init();
	all.mlx.win_ptr = mlx_new_window(all.mlx.mlx_ptr, 1920, 1080, "The Moving Circle");
	all.img.img_ptr = mlx_new_image(all.mlx.mlx_ptr, 1920, 1080);
	all.img.buffer = mlx_get_data_addr(all.img.img_ptr, &all.img.bits_per_pixel, &all.img.size_line, &all.img.endian);
	draw_circle(&all.img, all.pos.x, all.pos.y, 100, 0xFF0000);
	mlx_hook(all.mlx.win_ptr, 2, 0, &key_press, &all);
	mlx_loop_hook(all.mlx.mlx_ptr, &moving_circle, &all);
//	mlx_put_image_to_window(all.mlx.mlx_ptr, all.mlx.win_ptr, all.img.img_ptr, 0, 0);
	mlx_loop(all.mlx.mlx_ptr);
}
