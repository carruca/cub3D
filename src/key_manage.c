/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:25:30 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/08 14:32:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_move(t_all *all, double x, double y)
{
	if (all->map[(int)(all->pos.x + x * all->pos.mspeed)][(int)all->pos.y]
			!= '1')
		all->pos.x += x * all->pos.mspeed;
	if (all->map[(int)all->pos.x][(int)(all->pos.y + y * all->pos.mspeed)]
			!= '1')
		all->pos.y += y * all->pos.mspeed;
	display(all);
}

void	player_rotate(t_all *all, double speed)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = all->dir.x;
	all->dir.x = all->dir.x * cos(speed)
					- all->dir.y * sin(speed);
	all->dir.y = olddir_x * sin(speed)
					+ all->dir.y * cos(speed);
	oldplane_x = all->plane.x;
	all->plane.x = all->plane.x * cos(speed)
					- all->plane.y * sin(speed);
	all->plane.y = oldplane_x * sin(speed)
					+ all->plane.y * cos(speed);
	display(all);
}

int		key_core(t_all *all)
{
	if (all->keyboard[W_KEY])
		player_move(all, all->dir.x, all->dir.y);
	if (all->keyboard[LEFT_KEY])
		player_rotate(all, all->pos.rspeed);
	if (all->keyboard[D_KEY])
		player_move(all, all->plane.x, all->plane.y);
	if (all->keyboard[S_KEY])
		player_move(all, -all->dir.x, -all->dir.y);
	if (all->keyboard[RIGHT_KEY])
		player_rotate(all, -all->pos.rspeed);
	if (all->keyboard[A_KEY])
		player_move(all, -all->plane.x, -all->plane.y);
	if (all->keyboard[ESC_KEY])
		program_exit(all);
		return (0);
}

int		key_release(int keycode, t_all *all)
{
	all->keyboard[keycode] = 0;
	return (0);
}

int		key_press(int keycode, t_all *all)
{
	all->keyboard[keycode] = 1;
	return (0);
}
/*
int		key_press(int keycode, t_all *all)
{
	if (keycode == W_KEY)
		player_move(all, all->dir.x, all->dir.y);
	if (keycode == LEFT_KEY)
		player_rotate(all, all->pos.rspeed);
	if (keycode == D_KEY)
		player_move(all, all->plane.x, all->plane.y);
	if (keycode == S_KEY)
		player_move(all, -all->dir.x, -all->dir.y);
	if (keycode == RIGHT_KEY)
		player_rotate(all, -all->pos.rspeed);
	if (keycode == A_KEY)
		player_move(all, -all->plane.x, -all->plane.y);
	if (keycode == ESC_KEY)
		program_exit(all);
	return (1);
}*/
