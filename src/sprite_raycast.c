/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:28:31 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/08 15:33:43 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	sprite_calculate(t_all *all)
{
	all->draw.sprite.height = abs((int)(all->win.height /
								all->draw.sprite.transform.y));
	all->draw.sprite.start.y = (all->win.height / 2) -
								(all->draw.sprite.height / 2);
	if (all->draw.sprite.start.y < 0)
		all->draw.sprite.start.y = 0;
	all->draw.sprite.end.y = all->draw.sprite.start.y + all->draw.sprite.height;
	if (all->draw.sprite.end.y >= all->win.height)
		all->draw.sprite.end.y = all->win.height;
	all->draw.sprite.width = abs((int)(all->win.height /
								all->draw.sprite.transform.y));
	all->draw.sprite.start.x = all->draw.sprite.win -
								(all->draw.sprite.width / 2);
	if (all->draw.sprite.start.x < 0)
		all->draw.sprite.start.x = 0;
	all->draw.sprite.end.x = all->draw.sprite.width / 2 + all->draw.sprite.win;
	if (all->draw.sprite.end.x >= all->win.width)
		all->draw.sprite.end.x = all->win.width;
}

static void	sprite_translate_to_camera(t_all *all, int i)
{
	all->draw.sprite.x = all->sprite[all->sprite_order[i]].x - all->pos.x;
	all->draw.sprite.y = all->sprite[all->sprite_order[i]].y - all->pos.y;
	all->draw.sprite.inver = 1.0 /
		(all->plane.x * all->dir.y - all->dir.x * all->plane.y);
	all->draw.sprite.transform.x = all->draw.sprite.inver *
								(all->dir.y * all->draw.sprite.x
								- all->dir.x * all->draw.sprite.y);
	all->draw.sprite.transform.y = all->draw.sprite.inver *
								(-all->plane.y * all->draw.sprite.x
								+ all->plane.x * all->draw.sprite.y);
	all->draw.sprite.win = (int)((all->win.width / 2) *
			(1 + all->draw.sprite.transform.x / all->draw.sprite.transform.y));
}

static void	sprite_projection(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->sprite_count)
	{
		sprite_translate_to_camera(all, i);
		sprite_calculate(all);
		sprite_draw(all);
		i++;
	}
}

static void	sprite_sort(int *order, double *dist, int count)
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

void		sprite_raycast(t_all *all)
{
	int		i;

	i = 0;
	while (i < all->sprite_count)
	{
		all->sprite_order[i] = i;
		all->sprite_dist[i] = pow(all->pos.x - all->sprite[i].x, 2)
							+ pow(all->pos.y - all->sprite[i].y, 2);
		i++;
	}
	sprite_sort(all->sprite_order, all->sprite_dist, all->sprite_count);
	sprite_projection(all);
}
