/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:48:46 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/21 14:52:10 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	image_render(t_all *all)
{
	all->img.ptr = mlx_new_image(all->mlx.ptr, all->win.width, all->win.height);
	all->img.buffer = mlx_get_data_addr(all->img.ptr, &all->img.bits_per_pixel,
										&all->img.size_line, &all->img.endian);
	wall_raycast(all);
	sprite_raycast(all);
}

int		display(t_all *all)
{
	image_render(all);
	mlx_clear_window(all->mlx.ptr, all->win.ptr);
	mlx_put_image_to_window(all->mlx.ptr, all->win.ptr, all->img.ptr, 0, 0);
	mlx_destroy_image(all->mlx.ptr, all->img.ptr);
	return (1);
}

void	speed_init(t_all *all)
{
	all->draw.z_buffer = (double*)malloc(all->win.width * sizeof(double));
	all->pos.mspeed = 0.15;
	all->pos.rspeed = 0.05;
}

int		window_init(t_all *all)
{
	all->mlx.ptr = mlx_init();
	all->win.ptr = mlx_new_window(all->mlx.ptr, all->win.width,
									all->win.height, "cub3D");
	speed_init(all);
	texture_init(all);
	display(all);
	mlx_hook(all->win.ptr, 2, 0, &key_press, all);
	mlx_hook(all->win.ptr, 3, 0, &key_release, all);
	mlx_hook(all->win.ptr, 17, 0, &program_exit, all);
	mlx_loop_hook(all->mlx.ptr, &key_core, all);
	mlx_loop(all->mlx.ptr);
	return (1);
}
