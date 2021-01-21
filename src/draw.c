/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:21:01 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/21 11:49:27 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->buffer + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		vertical_draw(t_all *all, int x, int i)
{
	int	y;
	int	color;

	y = 0;
	while (y < all->win.height)
	{
		if (y < all->draw.start)
			my_mlx_pixel_put(&all->img, x, y, all->draw.c_rgb);
		if (y >= all->draw.start && y <= all->draw.end)
		{
			all->tex[i].y = (int)all->tex[i].pos & (all->tex[i].height - 1);
			all->tex[i].pos += all->tex[i].step;
			color = all->tex[i].img->buff[all->tex[i].height *
										all->tex[i].y + all->tex[i].x];
			my_mlx_pixel_put(&all->img, x, y, color);
		}
		if (y > all->draw.end)
			my_mlx_pixel_put(&all->img, x, y, all->draw.f_rgb);
		y++;
	}
}

static void	sprite_texture_x_calculate(t_all *all, int x)
{
	all->tex[4].x = (int)(256 * (x - (all->draw.sprite.win -
					all->draw.sprite.width / 2)) * all->tex[4].width /
					all->draw.sprite.width) / 256;
}

static void	sprite_texture_y_calculate(t_all *all, int y)
{
	all->tex[4].y = (((y * 256 - all->win.height * 128 +
					all->draw.sprite.height * 128) *
					all->tex[4].height) / all->draw.sprite.height) / 256;
}

void		sprite_draw(t_all *all)
{
	int	x;
	int	y;
	int	color;

	x = all->draw.sprite.start.x;
	while (x < all->draw.sprite.end.x && x <= all->win.width)
	{
		sprite_texture_x_calculate(all, x);
		if (x >= 0 && all->draw.sprite.transform.y > 0 &&
				all->draw.sprite.transform.y < all->draw.z_buffer[x])
		{
			y = all->draw.sprite.start.y;
			while (y < all->draw.sprite.end.y && y <= all->win.height + 1)
			{
				sprite_texture_y_calculate(all, y);
				color = all->tex[4].img->buff[all->tex[4].width *
					all->tex[4].y + all->tex[4].x];
				if (color != 0)
					my_mlx_pixel_put(&all->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}
