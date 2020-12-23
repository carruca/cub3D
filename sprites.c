/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:14:02 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/23 17:13:27 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//sort sprites from far in first position to the close in last.
void	sprite_sort(int *order, double *dist, int count)
{
	double	dist_tmp;
	int		order_tmp;
	int		sprite;
	int		i;

	i = 0;
	while (i < count - 1)
	{
		sprite = 0;
		while (sprite < count - 1)
		{
			if (dist[sprite] < dist[sprite + 1])
			{
				dist_tmp = dist[sprite + 1];
				dist[sprite + 1] = dist[sprite];
				dist[sprite] = dist_tmp;
				order_tmp = order[sprite + 1];
				order[sprite + 1] = order[sprite];
				order[sprite] = order_tmp;
			}
			sprite++;
		}
		i++;
	}
}

void	sprite_draw(t_all *all)
{
	int	x;
	int	y;
	int	color;

	x = all->draw.sprite.start.x;
	while (x < all->draw.sprite.end.x)
	{
		all->tex[4].x = (int)(256 * (x - (all->draw.sprite.win - all->draw.sprite.width / 2)) * all->tex[4].width / all->draw.sprite.width) / 256;
		if (x > 0 && x < all->win.height && all->draw.sprite.transform.y > 0 && all->draw.sprite.transform.y < all->draw.z_buffer[x])
		{
			y = all->draw.sprite.start.y;
			while (y < all->draw.sprite.end.y)
			{
				all->tex[4].y = (((y * 256 - all->win.height * 128 + all->draw.sprite.height * 128) * all->tex[4].height) / all->draw.sprite.height) / 256;
				color = all->tex[4].img->buff[all->tex[4].width * all->tex[4].y + all->tex[4].x];
				if (color != 0)
					my_mlx_pixel_put(&all->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

void	sprite_raycast(t_all *all)
{
	int		i;

	i = 0;
	while (i < all->sprite_count)
	{
		all->sprite_order[i] = i;
		all->sprite_dist[i] = pow(all->pos.x - all->sprite[i].x, 2) + pow(all->pos.y - all->sprite[i].y, 2);
		i++;
	}
	sprite_sort(all->sprite_order, all->sprite_dist, all->sprite_count);

	//after sorting the sprites, do the projection and draw them
	i = 0;
	while (i < all->sprite_count)
	{
		//translate sprite position to relative to camera
		all->draw.sprite.x = all->sprite[all->sprite_order[i]].x - all->pos.x;
		all->draw.sprite.y = all->sprite[all->sprite_order[i]].y - all->pos.y;

		all->draw.sprite.inver = 1.0 / (all->plane.x * all->dir.y - all->dir.x * all->plane.y);

		all->draw.sprite.transform.x = all->draw.sprite.inver * (all->dir.y * all->draw.sprite.x - all->dir.x * all->draw.sprite.y);
		all->draw.sprite.transform.y = all->draw.sprite.inver * (-1 * all->plane.y * all->draw.sprite.x + all->plane.x * all->draw.sprite.y);

		all->draw.sprite.win = (int)((all->win.width / 2) * (1 + all->draw.sprite.transform.x / all->draw.sprite.transform.y));

		//calculate height of the sprite on the screen
		all->draw.sprite.height = abs((int)(all->win.height / all->draw.sprite.transform.y));
		//calculate lowest and highet pixel to fill in current stripe
		all->draw.sprite.start.y = (all->win.height / 2) - (all->draw.sprite.height / 2);
		if (all->draw.sprite.start.y < 0)
			all->draw.sprite.start.y = 0;
		all->draw.sprite.end.y = all->draw.sprite.start.y + all->draw.sprite.height;
		if (all->draw.sprite.end.y >= all->win.height)
			all->draw.sprite.end.y = all->win.height - 1;
		//calculate width of the sprite
		all->draw.sprite.width = abs((int)(all->win.width / all->draw.sprite.transform.y));
		all->draw.sprite.start.x = all->draw.sprite.win - (all->draw.sprite.width / 2);
		if (all->draw.sprite.start.x < 0)
			all->draw.sprite.start.x = 0;
		all->draw.sprite.end.x = all->draw.sprite.start.x + all->draw.sprite.width;
		if (all->draw.sprite.end.x >= all->win.width)
			all->draw.sprite.end.x = all->win.width - 1;

		//loop throught every vertical stripe of the sprite on screen
		sprite_draw(all);
		i++;
	}
}
