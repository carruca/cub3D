/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:16:24 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/08 14:20:34 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		texture_sort(t_all *all)
{
	int	tex;

	tex = 0;
	if (all->ray.wall.side == 1)
	{
		if (all->ray.dir.y > 0)
			tex = 2;
		else
			tex = 3;
	}
	else
	{
		if (all->ray.dir.x > 0)
			tex = 1;
		else
			tex = 0;
	}
	return (tex);
}

void	texture_calculate(t_all *all, int i)
{
	if (all->ray.wall.side == 0)
		all->ray.wall.x = all->pos.y + all->ray.wall.dist * all->ray.dir.y;
	else
		all->ray.wall.x = all->pos.x + all->ray.wall.dist * all->ray.dir.x;
	all->ray.wall.x -= floor(all->ray.wall.x);
	all->tex[i].x = (int)(all->ray.wall.x * (double)all->tex[i].width);
	if (all->ray.wall.side == 0 && all->ray.dir.x > 0)
		all->tex[i].x = all->tex[i].width - all->tex[i].x - 1;
	if (all->ray.wall.side == 1 && all->ray.dir.y < 0)
		all->tex[i].x = all->tex[i].width - all->tex[i].x - 1;
	all->tex[i].step = 1.0 * all->tex[i].height / all->draw.height;
	all->tex[i].pos = (all->draw.start - all->win.height / 2 +
						all->draw.height / 2) * all->tex[i].step;
}

void	texture_init(t_all *all)
{
	size_t	i;

	i = 0;
	while (i < 5)
	{
		if (!(all->tex[i].img = mlx_xpm_file_to_image(all->mlx.ptr,
						all->tex[i].path, &all->tex[i].width,
						&all->tex[i].height)))
			error_put(12);
		if (!(all->tex[i].img->buff = (int*)mlx_get_data_addr(all->tex[i].img,
					&all->tex[i].img->bits_per_pixel,
					&all->tex[i].img->size_line, &all->tex[i].img->endian)))
			error_put(12);
		i++;
	}
}
