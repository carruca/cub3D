/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:34:39 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/29 14:25:00 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char	*fileheader_create(t_bmp bmp)
{
	unsigned char	*fileheader;
	
	fileheader = NULL;
	return (fileheader);
}

int		bitmap_save(t_all *all)
{
	t_bmp	bmp;
	int		fd;

	if (!(fd = open("screenshot.bmp", O_CREAT | O_WRONLY, S_IRWXU)))
		return (0);
	ft_bzero(&bmp, sizeof(bmp));
	bmp.width = all->win.width;
	bmp.height = all->win.height;
	bmp.fileheader = fileheader_create(bmp);
	close(fd);
	return (1);
}
