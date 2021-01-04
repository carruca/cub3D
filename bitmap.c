/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:34:39 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/04 16:11:43 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				color_get(t_all *all, t_bmp bmp, int x, int y)
{
	int	color;

	color = *(int*)(all->img.buffer + (4 * bmp.width * (bmp.height - 1 - y)) + (4 * x));
	return ((color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF));
}

int				pixel_data_write(t_all *all, t_bmp bmp, int fd)
{
	int						x;
	int						y;
	int						color;
//	static unsigned char	zero[4];

//	ft_bzero(zero, sizeof(zero));
	y = 0;
	while (y < bmp.height)
	{
		x = 0;
		while (x < bmp.width)
		{
			color = color_get(all, bmp, x, y);
			write(fd, &color, 3);
	//		if (bmp.padding > 0)
	//		{
	//			write(fd, &zero, bmp.padding);
	//			return (0);
	//		}
			x++;
		}
		y++;
	}
	return (1);
}

void			pixel_data_write_2(t_all *all, t_bmp bmp, int fd)
{
	int				x;
	int				y;
	unsigned char	pixel[4];

	ft_bzero(pixel, sizeof(pixel));
	y = bmp.width * (bmp.height - 1);
	while (y >= 0)
	{
		x = 0;
		while (x < bmp.width)
		{
			pixel[0] = (unsigned char)(int)(all->img.buffer[y]);
			pixel[0] = (unsigned char)(int)(all->img.buffer[y] >> 8);
			pixel[0] = (unsigned char)(int)(all->img.buffer[y] >> 16);
			pixel[0] = (unsigned char)(0);
			write(fd, pixel, 4);
			y++;
			x++;
		}
		y -= bmp.width * 2;
	}
}


unsigned char	*infoheader_write(t_bmp bmp)
{
	static unsigned char	infoheader[40];

	ft_bzero(infoheader, sizeof(infoheader));
	infoheader[0] = (unsigned char)sizeof(infoheader);
	infoheader[4] = (unsigned char)(bmp.width);
	infoheader[5] = (unsigned char)(bmp.width >> 8);
	infoheader[6] = (unsigned char)(bmp.width >> 16);
	infoheader[7] = (unsigned char)(bmp.width >> 24);
	infoheader[8] = (unsigned char)(bmp.height);
	infoheader[9] = (unsigned char)(bmp.height >> 8);
	infoheader[10] = (unsigned char)(bmp.height >> 16);
	infoheader[11] = (unsigned char)(bmp.height >> 24);
	infoheader[12] = (unsigned char)1;
	infoheader[14] = (unsigned char)24;
	return (infoheader);
}

unsigned char	*fileheader_write(t_bmp bmp)
{
	static unsigned char	fileheader[14];
	int						size_file;
	
	ft_bzero(fileheader, sizeof(fileheader));
	size_file = 54 + (bmp.width * bmp.height * 3);
	fileheader[0] = (unsigned char)0x42;
	fileheader[1] = (unsigned char)0x4D;
	fileheader[2] = (unsigned char)(size_file);
	fileheader[3] = (unsigned char)(size_file >> 8);
	fileheader[4] = (unsigned char)(size_file >> 16);
	fileheader[5] = (unsigned char)(size_file >> 24);
	fileheader[10] = (unsigned char)54; 
	return (fileheader);
}

int				bitmap_save(t_all *all)
{
	t_bmp	bmp;
	int		fd;

	if (!(fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)))
		return (0);
	ft_bzero(&bmp, sizeof(bmp));
	bmp.width = all->win.width;
	bmp.height = all->win.height;
//	bmp.padding = (4 - (bmp.width * 3) % 4) % 4;
	bmp.fileheader = fileheader_write(bmp);
	write(fd, bmp.fileheader, 14);
	bmp.infoheader = infoheader_write(bmp);
	write(fd, bmp.infoheader, 40);
	all->mlx.ptr = mlx_init();
	all->win.ptr = mlx_new_window(all->mlx.ptr, all->win.width, all->win.height, "cub3D");
	init(all);
	texture_init(all);
	image_create(all);
	pixel_data_write(all, bmp, fd);
	mlx_destroy_image(all->mlx.ptr, all->img.ptr);
	ft_putstr_fd("Bitmap image file created!\n", 1);
	close(fd);
	program_exit(all);
	return (1);
}
