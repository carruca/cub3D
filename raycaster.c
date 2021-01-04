/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:44:18 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/04 15:50:27 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	norm(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

double	dist(double x1, double x2)
{
	return (sqrt(1 + (pow(x1, 2) / pow(x2, 2))));
}

int		key_press(int keycode, t_all *all)
{
	double	olddir_x;
	double	oldplane_x;

	if (keycode == W_KEY)
	{
		if (all->map[(int)(all->pos.x + all->dir.x * all->pos.mspeed)][(int)all->pos.y] != '1')
			all->pos.x += all->dir.x * all->pos.mspeed;
		if (all->map[(int)all->pos.x][(int)(all->pos.y + all->dir.y * all->pos.mspeed)] != '1')
			all->pos.y += all->dir.y * all->pos.mspeed;
	}
	if (keycode == LEFT_KEY)
	{
		olddir_x = all->dir.x;
		all->dir.x = all->dir.x * cos(all->pos.rspeed) - all->dir.y * sin(all->pos.rspeed);
		all->dir.y = olddir_x * sin(all->pos.rspeed) + all->dir.y * cos(all->pos.rspeed);
		oldplane_x = all->plane.x;
		all->plane.x = all->plane.x * cos(all->pos.rspeed) - all->plane.y * sin(all->pos.rspeed);
		all->plane.y = oldplane_x * sin(all->pos.rspeed) + all->plane.y * cos(all->pos.rspeed);
//		printf("Xolddir=%f\nXdir=%f\nYdir=%f\nRotSpeed=%f\nXoldplane=%f\nXplane=%f\nYplane=%f\n", olddir_x, all->dir.x, all->dir.y, all->pos.rspeed, oldplane_x, all->plane.x, all->plane.y);
	}
	if (keycode == D_KEY)
	{
		if (all->map[(int)(all->pos.x + all->plane.x * all->pos.mspeed)][(int)all->pos.y] != '1')
			all->pos.x += all->plane.x * all->pos.mspeed;
		if (all->map[(int)all->pos.x][(int)(all->pos.y + all->plane.y * all->pos.mspeed)] != '1')
			all->pos.y += all->plane.y * all->pos.mspeed;
	}
	if (keycode == S_KEY)
	{
		if (all->map[(int)(all->pos.x - all->dir.x * all->pos.mspeed)][(int)all->pos.y] != '1')
			all->pos.x -= all->dir.x * all->pos.mspeed;
		if (all->map[(int)all->pos.x][(int)(all->pos.y - all->dir.y * all->pos.mspeed)] != '1')
			all->pos.y -= all->dir.y * all->pos.mspeed;
	}
	if (keycode == RIGHT_KEY)
	{
		olddir_x = all->dir.x;
		all->dir.x = all->dir.x * cos(-all->pos.rspeed) - all->dir.y * sin(-all->pos.rspeed);
		all->dir.y = olddir_x * sin(-all->pos.rspeed) + all->dir.y * cos(-all->pos.rspeed);
		oldplane_x = all->plane.x;
		all->plane.x = all->plane.x * cos(-all->pos.rspeed) - all->plane.y * sin(-all->pos.rspeed);
		all->plane.y = oldplane_x * sin(-all->pos.rspeed) + all->plane.y * cos(-all->pos.rspeed);
	}
	if (keycode == A_KEY)
	{
		if (all->map[(int)(all->pos.x - all->plane.x * all->pos.mspeed)][(int)all->pos.y] != '1')
			all->pos.x -= all->plane.x * all->pos.mspeed;
		if (all->map[(int)all->pos.x][(int)(all->pos.y - all->plane.y * all->pos.mspeed)] != '1')
			all->pos.y -= all->plane.y * all->pos.mspeed;
	}
	if (keycode == ESC_KEY)
		program_exit(all);
	return (1);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->buffer + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	screen_draw(t_all *all)
{
	int	x;
	int	y;

	x = 0;
	while (x < all->win.width)
	{
		y = 0;
		while (y < all->win.height)
		{
			my_mlx_pixel_put(&all->img, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}

void	vertical_draw(t_all *all, int x, int y1, int y2, int i)
{
	int	y;
	int	color;

	y = 0;
	while (y < all->win.height)
	{
		if (y < y1)
			my_mlx_pixel_put(&all->img, x, y, all->draw.c_rgb);
		if (y >= y1 && y <= y2)
		{
			//cast the texture coordinate to integer, and mask with (HEIGHT_TEX - 1) in case of overflow
			all->tex[i].y = (int)all->tex[i].pos & (all->tex[i].height - 1);
			all->tex[i].pos += all->tex[i].step;
			color = all->tex[i].img->buff[all->tex[i].height * all->tex[i].y + all->tex[i].x];
			my_mlx_pixel_put(&all->img, x, y, color);
		}
		if (y > y2)
			my_mlx_pixel_put(&all->img, x, y, all->draw.f_rgb);
		y++;
	}
}

void	texture_init(t_all *all)
{
	size_t	i;

	i = 0;
	while (i < 5)
	{
	//		printf("tex.img=%p\nmlx.ptr=%p\ntex.no_path=%s\nwidth=%i\nheight=%i\n", all->tex.img, all->mlx.ptr, all->tex.num[i], all->tex.width, all->tex.height);
		if (!(all->tex[i].img = mlx_xpm_file_to_image(all->mlx.ptr, all->tex[i].path, &all->tex[i].width, &all->tex[i].height)))
			error_put(12);
		if (!(all->tex[i].img->buff = (int*)mlx_get_data_addr(all->tex[i].img, &all->tex[i].img->bits_per_pixel, &all->tex[i].img->size_line, &all->tex[i].img->endian)))
			error_put(12);
		i++;
	}
}

void	textures_calculate(t_all *all, int i)
{
	//calculate value of wall.x
	if (all->ray.wall.side == 0)
		all->ray.wall.x = all->pos.y + all->ray.wall.dist * all->ray.dir.y;
	else
		all->ray.wall.x = all->pos.x + all->ray.wall.dist * all->ray.dir.x;
//	printf("Ypos=%f\nWalldist=%f\nYraydir=%f\nWalldist*Yraydir=%f\nWallX=%f\n--------------\n---------------\n", all->pos.y, all->ray.wall.dist, all->ray.dir.y, all->ray.wall.dist * all->ray.dir.y, all->ray.wall.x);
	all->ray.wall.x -= floor(all->ray.wall.x);

	//x coordinate on the texture
	all->tex[i].x = (int)(all->ray.wall.x * (double)all->tex[i].width);
	if (all->ray.wall.side == 0 && all->ray.dir.x > 0)
		all->tex[i].x = all->tex[i].width - all->tex[i].x - 1;
	if (all->ray.wall.side == 1 && all->ray.dir.y < 0)
		all->tex[i].x = all->tex[i].width - all->tex[i].x - 1;	
	//how much to increase the texture coordinate per screen pixel
	all->tex[i].step = 1.0 * all->tex[i].height / all->draw.height;
	//starting texture coordinate
	all->tex[i].pos = (all->draw.start - all->win.height / 2 + all->draw.height / 2) * all->tex[i].step;
//	printf("Xtex=%d\nYtex=%d\nPostex=%f\nSteptex=%f\nColor=%x\n------------\n--------------\n", all->tex.x, all->tex.y, all->tex.pos, all->tex.step, all->color);
}

/*
void	render(t_all *all)
{
	int	x;

	x = 0;
}*/

void	wall_raycast(t_all *all)
{
	int	tex;

	all->ray.x = 0;
	while (all->ray.x < all->win.width)
	{
	//	printf("-------\n---------\n---------------------Rray%i\n", all->ray.x);
	//	printf("Xcam=%f\nXraydir=%f\nYraydir=%f\nXdir=%f\nYdir=%f\nXplane=%f\nYplane=%f\n", all->ray.cam.x, all->ray.dir.x, all->ray.dir.y, all->dir.x, all->dir.y, all->plane.x, all->plane.y);
	//	printf("Xwin=%i\n", all->win.width);
		all->ray.cam.x = (2 * all->ray.x) / (double)all->win.width - 1;
	//	printf("Rray=%d\nXwin=%i\n", all->ray.x, all->win.width);
		all->ray.dir.x = all->dir.x + all->plane.x * all->ray.cam.x;
		all->ray.dir.y = all->dir.y + all->plane.y * all->ray.cam.x;
	//	printf("Xcam=%f\nXraydir=%f\nYraydir=%f\nXdir=%f\nYdir=%f\nXplane=%f\nYplane=%f\n", all->ray.cam.x, all->ray.dir.x, all->ray.dir.y, all->dir.x, all->dir.y, all->plane.x, all->plane.y);

		//which box of the map we're in
		all->maze.x = (int)all->pos.x;
		all->maze.y = (int)all->pos.y;
	//	printf("Xmaze=%d\nYmaze=%d\nXpos=%f\nYpos=%f\n", all->maze.x, all->maze.y, all->pos.x, all->pos.y);
		//lenght of the ray from one x or y-side to next x or y-side
//		all->ray.delta.x = fabs(1.0 / all->ray.dir.x);
//		all->ray.delta.y = fabs(1.0 / all->ray.dir.y);
		all->ray.delta.x = dist(all->ray.dir.y, all->ray.dir.x);
		all->ray.delta.y = dist(all->ray.dir.x, all->ray.dir.y); 

		//calcullate step and initial side
		if (all->ray.dir.x < 0)
		{
			all->ray.step.x = -1;
			all->ray.side.dist.x = (all->pos.x - all->maze.x) * all->ray.delta.x;
		}
		else
		{
			all->ray.step.x = 1;
			all->ray.side.dist.x = (all->maze.x + 1.0 - all->pos.x) * all->ray.delta.x;
		}
		if (all->ray.dir.y < 0)
		{
			all->ray.step.y = -1;
			all->ray.side.dist.y = (all->pos.y - all->maze.y) * all->ray.delta.y;
		}
		else
		{
			all->ray.step.y = 1;
			all->ray.side.dist.y = (all->maze.y + 1.0 - all->pos.y) * all->ray.delta.y;
		}
	//	printf("Xsidedist=%f\nYsidedisst=%f\nXdelta=%f\nYdelta=%f\n", all->ray.side.dist.y, all->ray.side.dist.y, all->ray.delta.x, all->ray.delta.y);
		//was there a wall hit?
		all->ray.wall.hit = 0;
		//perform DDA algorithm
		while (all->ray.wall.hit == 0)
		{
	//		printf("-------\n-----\n");
	//		printf("Xmaze=%d\nYmaze=%d\nXpos=%f\nYpos=%f\n", all->maze.x, all->maze.y, all->pos.x, all->pos.y);
		//	printf("Xcam=%f\nXraydir=%f\nYraydir=%f\nXdir=%f\nYdir=%f\nXplane=%f\nYplane=%f\n", all->ray.cam.x, all->ray.dir.x, all->ray.dir.y, all->dir.x, all->dir.y, all->plane.x, all->plane.y);
	//		printf("Xsidedist=%f\nYsidedisst=%f\nXdelta=%f\nYdelta=%f\nXstep=%d\nYstep=%d\n", all->ray.side.dist.y, all->ray.side.dist.y, all->ray.delta.x, all->ray.delta.y, all->ray.step.x, all->ray.step.y);
			//jump to next map square, OR in x-direction, OR in y-direction
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
	//		printf("---------XYmap=%c\n", all->map[all->maze.x][all->maze.y]);
	//		printf("---------Xmaze=%d\n--------Ymaze=%d\n", all->maze.x, all->maze.y);
			if (all->map[all->maze.x][all->maze.y] == '1')
				all->ray.wall.hit = 1;
		}
	//	printf("walldist=%f\n", all->ray.wall.dist);
	//	printf("2.Xcam=%f\n2.Xraydir=%f\n2.Yraydir=%f\n2.Xdir=%f\n2.Ydir=%f\n2.Xplane=%f\n2.Yplane=%f\n", all->ray.cam.x, all->ray.dir.x, all->ray.dir.y, all->dir.x, all->dir.y, all->plane.x, all->plane.y);
	//	printf("2.Xmaze=%d\n2.Ymaze=%d\n2.Xpos=%f\n2.Ypos=%f\n", all->maze.x, all->maze.y, all->pos.x, all->pos.y);
		//calcuate distance projected on camera direction (Euclidean distance will give fisheye effect)
		if (all->ray.wall.side == 0)
			all->ray.wall.dist = (all->maze.x - all->pos.x + (1 - all->ray.step.x) / 2) / all->ray.dir.x;
		else
			all->ray.wall.dist = (all->maze.y - all->pos.y + (1 - all->ray.step.y) / 2) / all->ray.dir.y;
		//store distance in zbuffer(depth) for sprites
		all->draw.z_buffer[all->ray.x] = all->ray.wall.dist;
//		printf("z_buffer=%f\n", all->draw.z_buffer[all->ray.x]);
	//	printf("Ymaze=%d\nYpos=%f\nYstep=%d\nYraydir=%f\n", all->maze.y, all->pos.y, all->ray.step.y, all->ray.dir.y);
	//	printf("walldist=%f\n", all->ray.wall.dist);
		//calculate hight of line to draw on screen
		all->draw.height = all->win.height / all->ray.wall.dist;
		//calculate lowest and hightest pixel to fill in current stripe (line)
	//	all->draw.start = (-1 * all->draw.height / 2) + (all->win.height / 2);
		all->draw.start = (all->win.height / 2) - (all->draw.height / 2);
		if (all->draw.start < 0)
			all->draw.start = 0;
	//	all->draw.end = all->draw.height / 2 + all->win.height / 2;
		all->draw.end = all->draw.start + all->draw.height;
		if (all->draw.end >= all->win.height)
			all->draw.end = all->win.height - 1;

	//	printf("Xstep=%d\nYstep=%d\n", all->ray.step.x, all->ray.step.y);
		//sort texture to draw
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
		textures_calculate(all, tex);
		/*
		//choose color
		if (all->map[all->maze.x][all->maze.y] == '1')
			all->color = 0xFF007F;
		//give x and y sides different brightness
		if (all->ray.wall.side == 1)
		{
			all->color /= 2;
		}
		*/
		//draw the pixels of the stripe as vertical line
//		printf("Height=%i\nStart=%i\nEnd=%i\nColor=%x\n", all->draw.height, all->draw.start, all->draw.end, all->color);
		vertical_draw(all, all->ray.x, all->draw.start, all->draw.end, tex);
		all->ray.x++;
	}
}

void	image_create(t_all *all)
{
	all->img.ptr = mlx_new_image(all->mlx.ptr, all->win.width, all->win.height);
	all->img.buffer = mlx_get_data_addr(all->img.ptr, &all->img.bits_per_pixel, &all->img.size_line, &all->img.endian);
	wall_raycast(all);
	sprite_raycast(all);
}

int		display(t_all *all)
{
	image_create(all);
//	all->img.ptr = mlx_new_image(all->mlx.ptr, all->win.width, all->win.height);
//	all->img.buffer = mlx_get_data_addr(all->img.ptr, &all->img.bits_per_pixel, &all->img.size_line, &all->img.endian);
//	screen_draw(all);
//	vertical_draw(all, 639,225, 255, 0x7F8000);
//	wall_raycast(all);
//	sprite_raycast(all);
//	printf("Entra en el loop\n");
	mlx_clear_window(all->mlx.ptr, all->win.ptr);
	mlx_put_image_to_window(all->mlx.ptr, all->win.ptr, all->img.ptr, 0, 0);
	mlx_destroy_image(all->mlx.ptr, all->img.ptr);
//	all->img.ptr = mlx_new_image(all->mlx.ptr, all->win.width, all->win.height);
//	all->img.buffer = mlx_get_data_addr(all->img.ptr, &all->img.bits_per_pixel, &all->img.size_line, &all->img.endian);
	return (1);
}

int		init(t_all *all)
{

//	all->pos.x = 11;
//	all->pos.y = 12;
//	all->dir.x = -1;
//	all->dir.y = 0;
//	all->plane.x = 0;
//	all->plane.y = 0.66;	
	all->draw.z_buffer = (double*)malloc(all->win.width * sizeof(double));
	all->ray.cam.x = 0;
	all->ray.dir.x = 0;
	all->ray.dir.y = 0;
	all->maze.x = 0;
	all->maze.y = 0;
	all->ray.delta.x = 0;
	all->ray.delta.y = 0;
	all->ray.side.dist.x = 0;
	all->ray.side.dist.y = 0;
	all->ray.wall.dist = 0;
	all->draw.height = 0;
	all->draw.start = 0;
	all->draw.end = 0;
//	all->time = 0;
//	all->oldtime = 0;
	all->pos.mspeed = 0.25;
	all->pos.rspeed = 0.15;
//	all->ray.x = 0;
	return (1);
}

int		window_init(t_all *all)
{
	init(all);
	all->mlx.ptr = mlx_init();
	all->win.ptr = mlx_new_window(all->mlx.ptr, all->win.width, all->win.height, "cub3D");
//	all->img.ptr = mlx_new_image(all->mlx.ptr, all->win.width, all->win.height);
//	all->img.buffer = mlx_get_data_addr(all->img.ptr, &all->img.bits_per_pixel, &all->img.size_line, &all->img.endian);
//	screen_draw(all);
//	mlx_put_image_to_window(all->mlx.ptr, all->win.ptr, all->img.ptr, 0, 0);
	texture_init(all);
	mlx_hook(all->win.ptr, 2, 0, &key_press, all);
	mlx_hook(all->win.ptr, 17, 0, &program_exit, all);
	mlx_loop_hook(all->mlx.ptr, &display, all);
	mlx_loop(all->mlx.ptr);
	return (1);
}
