/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 10:34:02 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/22 16:18:06 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <limits.h>
# include <math.h>
# include "mlx/mlx.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define ESC_KEY	53
# define W_KEY		13
# define A_KEY		0
# define S_KEY		1
# define D_KEY		2
# define UP_KEY		126
# define DOWN_KEY	125
# define LEFT_KEY	123
# define RIGHT_KEY	124

typedef struct s_mlx
{
	void	*ptr;
}	t_mlx;

typedef struct s_win
{
	int		width;
	int		height;
	void	*ptr;
}	t_win;

typedef struct s_img
{
	void	*ptr;
	char	*buffer;
	int		*buff;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
//	int		offset;
}	t_img;

typedef struct s_color
{
	unsigned	r;
	unsigned	g;
	unsigned	b;
}	t_color;



typedef struct s_tex
{
//	char	*no_path;
//	char	*so_path;
//	char	*we_path;
//	char	*ea_path;
//	char	*s_path;
	char	*path;
	int		x;
	int		y;
	double	step;
	double	pos;
	t_img	*img;
	int		width;
	int		height;
//	int		*buffer;
//	int		bpp;
//	int		size_line;
//	int		endian;
//	int		f_red;
//	int		f_green;
//	int		f_blue;
//	int		c_red;
//	int		c_green;
//	int		c_blue;
}	t_tex;

typedef	struct s_dvec
{
	double	x;
	double	y;
}	t_dvec;

typedef struct s_ivec
{
	int	x;
	int	y;
}	t_ivec;

/*
typedef struct s_plane
{
	double	x;
	double	y;
}	t_plane;
*/
/*
typedef struct s_dir
{
	double	x;
	double	y;
}	t_dir;
*/
typedef	struct s_cam
{
	double	x;
//	double	y;
}	t_cam;

typedef struct s_side
{
	t_dvec	dist;
}	t_side;
/*
typedef struct s_delta
{
	double	x;
	double	y;
}	t_delta;
*/

typedef struct s_wall
{
	double	dist;
	int		hit;
	int		side;
	double	x;
}	t_wall;

typedef struct s_ray
{
	int		x;
/*	int		dof;
	int		mx;
	int		my;
	int		mp;
	int		size;
	int		speed;
	float	x;
	float	y;
	float	a;
	float	xo;
	float	yo;
	float	tan;
	float	ntan;
	float	dish;
	float	hx;
	float	hy;
	float	disv;
	float	vx;
	float	vy;
	float	dist;
	float	lineh;
	float	lineo;*/
	t_dvec	dir;
	t_cam	cam;
//	t_plane	plane;
	t_side	side;
	t_dvec	delta;
	t_wall	wall;
	t_ivec	step;
}	t_ray;

typedef struct s_draw
{
	int		height;
	int		start;
	int		end;
	int		f_rgb;
	int		c_rgb;
	double	*z_buffer;
//	t_vec	point1;
//	t_vec	point2;
//	t_ray	ray;
}	t_draw;
/*
typedef struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}	t_color;
*/
typedef struct s_map
{
	int	x;
	int y;
//	int	size;
//	int	map[64];
}	t_map;

typedef struct s_pos
{
	double	x;
	double	y;
	double	mspeed;
	double	rspeed;
//	float	px;
//	float	py;
//	float	pdx;
//	float	pdy;
//	float	pa;
//	float	fova;
//	float	raya;
}	t_pos;

typedef struct s_all
{
//	int			x;
//	int			y;
//	void		*win_ptr;
//	void		*mlx_ptr;
	t_mlx		mlx;
	t_win		win;
	t_img		img;
	t_ivec		maze;
	t_pos		pos;
	t_dvec		dir;
	t_dvec		plane;
	t_tex		tex[5];
	t_draw		draw;
	t_ray		ray;
	t_dvec		*sprite;
	int			sprite_count;	
	int			*sprite_order;
	double		*sprite_dist;
	char		**map;
	int			is_map;
	int			control;		
	int			map_rows;
	int			map_columns;
//	int			sprites;
	int			f_c;
	int			rows;
	int			control_player;
	int			color;
}	t_all;

//int	init_mlx(t_all *all);
int		window_init(t_all *all);
void	error_put(int errno);
int		program_exit(t_all *all);
void	sprite_raycast(t_all *all);
double	dist(double x1, double x2);

#endif
