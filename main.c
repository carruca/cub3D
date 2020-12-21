/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:15:48 by tsierra-          #+#    #+#             */
/*   Updated: 2020/11/12 12:45:49 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->buffer + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
 *	Funtions Colors:
*/

int		argb_to_color(unsigned a, unsigned r, unsigned g, unsigned b)
{
	unsigned color;

	color = a & 0xFF;
	color <<= 8;
	color |= r & 0xFF;
	color <<= 8;
	color |= g & 0xFF;
	color <<= 8;
	color |= b & 0xFF;
	return (color);
}

void	make_color_gradient(t_img *img, double frecuency1, double frecuency2, double frecuency3, double phase1, double phase2, double phase3, int len, int y)
{
	int width;
	int	center;
	float	i;
	float	r;
	float	g;
	float	b;

	width = 127;
	center = 128;
	i = 0;

	while (i < len)
	{
		if (i == (i / 5))
		r = 255 * sin((frecuency1 * i + phase1) * width + center);
		g = 255 * sin((frecuency2 * i + phase2) * width + center);
		b = 255 * sin((frecuency3 * i + phase3) * width + center);
		my_mlx_pixel_put(img, i, y, argb_to_color(0, r, g, b));
		i += 0.1;
	}
}

float	color_to_rainbow(double frecuency, int x)
{
	float	r;
	float	g;
	float	b;

	r = 255 * sin((frecuency * x + 2) * 127 + 128);
	g = 255 * sin((frecuency * x + 6) * 127 + 128);
	b = 255 * sin((frecuency * x + 8) * 127 + 128);
	return(argb_to_color(0, r, g, b));
}

int		add_gradient(int color1, int color2, float fraction)
{
	int	r1 = (color1 >> 16) & 0xFF;
	int	r2 = (color2 >> 16) & 0xFF;
	int	g1 = (color1 >> 8) & 0xFF;
	int	g2 = (color2 >> 8) & 0xFF;
	int	b1 = color1 & 0xFF;
	int	b2 = color2 & 0xFF;

	return ((int)((r2 - r1) * fraction + r1) << 16 |
			(int)((g2 - g2) * fraction + g1) << 8 |
			(int)((b2 - b1) * fraction + b1));
}

int		get_opposite(int color)
{
	return (color ^ 0xFFFFFF);
}

int		add_shade(double distance, int color)
{
	return (color * distance);
}

/*
 *	Funtions geometry
*/

void	draw_segment(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	double	x;
	double	y;

	x = x1;
	y = y1;
	while (x < x2)
	{
		my_mlx_pixel_put(img, x, y, color);
		x += 0.1;
		y = (x - x1) / (x2 - x1) * (y2 - y1) + y1;
	}
}

void	draw_triangle(t_img *img, int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
	draw_segment(img, x2, y2, x1, y1, color);
	draw_segment(img, x1, y1, x3, y3, color);
	draw_segment(img, x2, y2, x3, y3, color);
}

void	draw_square(t_img *img, int x, int y, int len_side, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < len_side)
	{
		i = 0;
		while (i < len_side)
		{
			if (j == 0 || j == len_side - 1) 
				my_mlx_pixel_put(img, x + i, y + j, color);
			if (i == 0 || i == len_side - 1)
				my_mlx_pixel_put(img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_circle(t_img *img, int x, int y, int r, int color)
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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}


int		draw_line(void *mlx_ptr, void *win_ptr, int beginX, int beginY, int endX, int endY, int color)
{
	double	deltaX;
	double	deltaY;
	int		pixels;
	double	pixelX;
	double	pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}

/*
int		mouse_event(t_cub program, void *param)
{
	mlx_pixel_put(program.mlx_ptr, program.win_ptr, 640/2, 360/2, 0xFFFFFF);
	return (1);
}
*/

int		main()
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
//	void		*img_ptr;
//	int			bits_per_pixel;
//	int			size_line;
//	int			endian;
//	int			*buffer;
//	int			color;
	int			x;
	int			y;
	int			radius;
//	int			pixel;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 500, "cub3D");

//	img.offset = (y * img.size_line + x * (img.bits_per_pixel / 8));
	
//	mlx_pixel_put(mlx_ptr, win_ptr, 320, 180, 0xBAE323);
//	mlx_string_put(mlx_ptr, win_ptr, 150, 155, 0xBAE323, "Carlos es el mejor");

//	draw_line(mlx_ptr, win_ptr, 640, 360, 0, 0, 0xFFFFFF);

//	mlx_key_hook(win_ptr, deal_key, (void *)0);

//	img.mlx_ptr = mlx_ptr;
//	img.win_ptr = win_ptr;

//	mlx_mouse_hook(win_ptr, &mouse_event, &img);

	img.img_ptr = mlx_new_image(mlx_ptr, 1000, 500);	
	img.buffer = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
//	color = 0xABCDEF;
//	color = get_opposite(color);
//	color = add_shade(1, color);
/*
	y = 0;
	color = 0xFF;
	while (y < 497)
	{
		x = 0;
		while (x < img.size_line)
		{
			color = color_to_rainbow(0.3, x + y);
			if (y < 500/2)
				my_mlx_pixel_put(&img, x, y, color);
			else
				my_mlx_pixel_put(&img, x, y, get_opposite(color));
			x++;
		}
		y++;
	}
*/
	radius = 1;
	while (radius < 100)
	{
		draw_circle(&img, 200, 250, radius, 0x000000);
		radius += 5;
	}
	draw_circle(&img, 200, 350, 100, 0x000000);
	draw_square(&img, 350, 150, 200, 0x000000);
	draw_triangle(&img, 750, 150, 600, 350, 900, 350, 0x000000);

	y = 0;
	while(y < 497)
	{
		make_color_gradient(&img, 0.33, 2.33, 6.33, 4, 8, 16, img.size_line, y);
		y++;
	}
	get_next_line(2, NULL);
	/*
	for(y = 0; y < 360; ++y)
	for(x = 0; x < 640; ++x)
	{
		if (y < 180)
			img.buffer[(y * img.size_line) + x] = color;
		else
		{
			color = 0xD69F8B;
			color = get_opposite(color);
			img.buffer[(y * img.size_line) + x] = color;
		}
	}
	my_mlx_pixel_put(img, 320, 240, 0x00FF0000);
	my_mlx_pixel_put(img, 320, 420, 0x00FF0000);
	my_mlx_pixel_put(img, 360, 240, 0x00FF0000);
	my_mlx_pixel_put(img, 360, 420, 0x00FF0000);
	x = 320;
	y = 240;
	while (x >= 320 && x <= 360 && (y == 240 || y == 420)) // Lado horizontal arriba
	{
		my_mlx_pixel_put(img, x, y, 0x00FF0000);
		x++;
	}
	x = 320;
	y = 420;
	while (x >= 320 && x <= 360 && y == 420) // Lado horizontal abajo
	{
		my_mlx_pixel_put(img, x, y, 0x00FF0000);
		x++;
	}
	x = 320;
	y = 240;
	while (y >= 240 && y <= 420 && x == 320) // Lado vertical izquierdo
	{
		my_mlx_pixel_put(img, x, y, 0x00FF0000);
		y++;
	}
	x = 360;
	y = 240;
	while (y >= 240 && y <= 420 && x == 360) // Lado vertical derecho
	{
		my_mlx_pixel_put(img, x, y, 0x00FF0000);
		y++;
	}

	if (bits_per_pixel != 32)
		color = mlx_get_color_value(mlx_ptr, color);
	for(y = 0; y < 360; ++y)
	for(x = 0; x < 640; ++x)
	{
		pixel = (y * size_line) + (x * 4);
		if (y < 180)
		{
			buffer[(y * size_line) + x] = color;
			if (endian == 1) // Most significant (Alpha) byte first
			{
				buffer[pixel + 0] = (color >> 24); // Alpha
				buffer[pixel + 1] = (color >> 16) & 0xFF; // Red
				buffer[pixel + 2] = (color >> 8) & 0xFF; // Green
				buffer[pixel + 3] = (color) & 0xFF; // Blue
			}	
			else if (endian == 0) // Least significant (Blue) byte first
			{
				buffer[pixel + 0] = (color) & 0xFF; // Blue
				buffer[pixel + 1] = (color >> 8) & 0xFF; // Green
				buffer[pixel + 2] = (color >> 16) & 0xFF; // Red
				buffer[pixel + 3] = (color >> 24); // Alpha
			}
		}
		else
		{
			color = 0xD69F8B;
			color = add_shade(1, color);
			buffer[(y * size_line) + x] = color;
 			if (endian == 1)
			{
				buffer[pixel + 0] = (color >> 24);
				buffer[pixel + 1] = (color >> 16) & 0xFF;
				buffer[pixel + 2] = (color >> 8) & 0xFF;
				buffer[pixel + 3] = (color) & 0xFF;
			}	
			else if (endian == 0)
			{
				buffer[pixel + 0] = (color) & 0xFF;
				buffer[pixel + 1] = (color >> 8) & 0xFF;
				buffer[pixel + 2] = (color >> 16) & 0xFF;
				buffer[pixel + 3] = (color >> 24);
			}

		}
	}
*/
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}
