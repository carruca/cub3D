/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:34:39 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/07 17:29:26 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pixel_data_write(int fd, t_all *all)
{
	char	*pixel_data;
	int		i;

	i = 0;
	pixel_data = (char*)all->img.buffer;
	while (i < all->win.height)
		write(fd, &pixel_data[i++ * (all->img.size_line * 4)],
				all->win.width * 16);
}

void	infoheader_write(int fd, t_all *all)
{
	static unsigned char	infoheader[40];

	ft_bzero(infoheader, sizeof(infoheader));
	infoheader[0] = (unsigned char)sizeof(infoheader);
	infoheader[4] = (unsigned char)(all->win.width);
	infoheader[5] = (unsigned char)(all->win.width >> 8);
	infoheader[6] = (unsigned char)(all->win.width >> 16);
	infoheader[7] = (unsigned char)(all->win.width >> 24);
	infoheader[8] = (unsigned char)(-all->win.height);
	infoheader[9] = (unsigned char)(-all->win.height >> 8);
	infoheader[10] = (unsigned char)(-all->win.height >> 16);
	infoheader[11] = (unsigned char)(-all->win.height >> 24);
	infoheader[12] = (unsigned char)1;
	infoheader[14] = (unsigned char)32;
	write(fd, infoheader, 40);
}

void	fileheader_write(int fd, t_all *all)
{
	static unsigned char	fileheader[14];
	int						size_file;

	ft_bzero(fileheader, sizeof(fileheader));
	size_file = 54 + (all->win.width * all->win.height * 4);
	fileheader[0] = (unsigned char)0x42;
	fileheader[1] = (unsigned char)0x4D;
	fileheader[2] = (unsigned char)(size_file);
	fileheader[3] = (unsigned char)(size_file >> 8);
	fileheader[4] = (unsigned char)(size_file >> 16);
	fileheader[5] = (unsigned char)(size_file >> 24);
	fileheader[10] = (unsigned char)54;
	write(fd, fileheader, 14);
}

int		bitmap_save(t_all *all)
{
	int		fd;

	if (!(fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)))
		return (0);
	fileheader_write(fd, all);
	infoheader_write(fd, all);
	all->mlx.ptr = mlx_init();
	all->win.ptr = mlx_new_window(all->mlx.ptr, all->win.width,
									all->win.height, "cub3D");
	speed_init(all);
	texture_init(all);
	image_render(all);
	pixel_data_write(fd, all);
	mlx_destroy_image(all->mlx.ptr, all->img.ptr);
	ft_putstr_fd("Bitmap image file created!\n", 1);
	close(fd);
	program_exit(all);
	return (1);
}
