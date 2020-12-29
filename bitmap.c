/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:34:39 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/29 18:04:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void			pixel_data_write(t_all *all, t_bmp bmp)
{
	int	x;
	int	y;

	x = 0;
	while (x < all->win.width)
	{
		y = 0;
		while (y < all->win.height)
		{
			y++;
		}
		x++;
	}
}*/

unsigned char	*infoheader_create(t_bmp bmp)
{
	static unsigned char	infoheader[40];

	ft_bzero(infoheader, sizeof(infoheader));
	infoheader[0] = (unsigned char)sizeof(infoheader);
	infoheader[4] = (unsigned char)(bmp.width >> 24);
	infoheader[5] = (unsigned char)(bmp.width >> 16);
	infoheader[6] = (unsigned char)(bmp.width >> 8);
	infoheader[7] = (unsigned char)bmp.width;
	infoheader[8] = (unsigned char)(bmp.height >> 24);
	infoheader[9] = (unsigned char)(bmp.height >> 16);
	infoheader[10] = (unsigned char)(bmp.height >> 8);
	infoheader[11] = (unsigned char)bmp.height;
	infoheader[12] = (unsigned char)1;
	infoheader[14] = (unsigned char)24;
	return (infoheader);
}

unsigned char	*fileheader_create(t_bmp bmp)
{
	static unsigned char	fileheader[14];
	int						size_file;
	
	ft_bzero(fileheader, sizeof(fileheader));
	size_file = 54 + (bmp.width * bmp.height * 3);
	fileheader[0] = (unsigned char)0x42;
	fileheader[1] = (unsigned char)0x4D;
	fileheader[2] = (unsigned char)(size_file >> 24);
	fileheader[3] = (unsigned char)(size_file >> 16);
	fileheader[4] = (unsigned char)(size_file >> 8);
	fileheader[5] = (unsigned char)size_file;
	fileheader[10] = (unsigned char)54; 
	return (fileheader);
}

int				bitmap_save(t_all *all)
{
	t_bmp	bmp;
	int		fd;

	if (!(fd = open("screenshot.bmp", O_CREAT | O_WRONLY, S_IRWXU)))
		return (0);
	ft_bzero(&bmp, sizeof(bmp));
	bmp.width = all->win.width;
	bmp.height = all->win.height;
//	padding = 
	bmp.fileheader = fileheader_create(bmp);
	write(fd, bmp.fileheader, 14);
	bmp.infoheader = infoheader_create(bmp);
	write(fd, bmp.infoheader, 40);
	ft_putstr_fd("Screenshot created!\n", 1);
	close(fd);
	return (1);
}
