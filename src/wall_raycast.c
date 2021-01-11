/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:08:11 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/08 14:14:21 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	vertical_calculate(t_all *all)
{
	all->draw.height = all->win.height / all->ray.wall.dist;
	all->draw.start = (all->win.height / 2) - (all->draw.height / 2);
	if (all->draw.start < 0)
		all->draw.start = 0;
	all->draw.end = all->draw.start + all->draw.height;
	if (all->draw.end >= all->win.height)
		all->draw.end = all->win.height - 1;
}

static void	wall_ray_distance_calculate(t_all *all)
{
	if (all->ray.wall.side == 0)
		all->ray.wall.dist = (all->maze.x - all->pos.x +
				(1 - all->ray.step.x) / 2) / all->ray.dir.x;
	else
		all->ray.wall.dist = (all->maze.y - all->pos.y +
				(1 - all->ray.step.y) / 2) / all->ray.dir.y;
}

static void	wall_ray_hit_calculate(t_all *all)
{
	all->ray.wall.hit = 0;
	while (all->ray.wall.hit == 0)
	{
		if (all->ray.side.dist.x < all->ray.side.dist.y)
		{
			all->ray.side.dist.x += all->ray.delta.x;
			all->maze.x += all->ray.step.x;
			all->ray.wall.side = 0;
		}
		else
		{
			all->ray.side.dist.y += all->ray.delta.y;
			all->maze.y += all->ray.step.y;
			all->ray.wall.side = 1;
		}
		if (all->map[all->maze.x][all->maze.y] == '1')
			all->ray.wall.hit = 1;
	}
}

static void	wall_ray_step_and_initial_side_calculate(t_all *all)
{
	if (all->ray.dir.x < 0)
	{
		all->ray.step.x = -1;
		all->ray.side.dist.x = (all->pos.x - all->maze.x) * all->ray.delta.x;
	}
	else
	{
		all->ray.step.x = 1;
		all->ray.side.dist.x = (all->maze.x + 1.0 - all->pos.x) *
								all->ray.delta.x;
	}
	if (all->ray.dir.y < 0)
	{
		all->ray.step.y = -1;
		all->ray.side.dist.y = (all->pos.y - all->maze.y) * all->ray.delta.y;
	}
	else
	{
		all->ray.step.y = 1;
		all->ray.side.dist.y = (all->maze.y + 1.0 - all->pos.y) *
								all->ray.delta.y;
	}
}

void		wall_raycast(t_all *all)
{
	int	tex;

	all->ray.x = 0;
	while (all->ray.x < all->win.width)
	{
		all->ray.cam.x = (2 * all->ray.x) / (double)all->win.width - 1;
		all->ray.dir.x = all->dir.x + all->plane.x * all->ray.cam.x;
		all->ray.dir.y = all->dir.y + all->plane.y * all->ray.cam.x;
		all->maze.x = (int)all->pos.x;
		all->maze.y = (int)all->pos.y;
		all->ray.delta.x = dist(all->ray.dir.y, all->ray.dir.x);
		all->ray.delta.y = dist(all->ray.dir.x, all->ray.dir.y);
		wall_ray_step_and_initial_side_calculate(all);
		wall_ray_hit_calculate(all);
		wall_ray_distance_calculate(all);
		all->draw.z_buffer[all->ray.x] = all->ray.wall.dist;
		vertical_calculate(all);
		tex = texture_sort(all);
		texture_calculate(all, tex);
		vertical_draw(all, all->ray.x, tex);
		all->ray.x++;
	}
}
