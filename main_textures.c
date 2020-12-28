/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:12:28 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/28 13:38:30 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main()
{
	t_all	all;
	char	*relative_path;
	int		img_width;
	int		img_height;

	relative_path = "./textures/texture-wall-gotele.xpm";
	all.mlx.mlx_ptr = mlx_init();
	all.mlx.win_ptr = mlx_new_window(all.mlx.mlx_ptr, 1920, 1080, "Textures");
	all.img.img_ptr = mlx_xpm_file_to_image(all.mlx.mlx_ptr, relative_path, &img_width, &img_height);
	printf("\n%i y %i\n", img_width, img_height);
	all.pos.x = 0;
	while (all.pos.x < 1920)
	{
		all.pos.y = 0;
		while (all.pos.y < 1080)
		{
			mlx_put_image_to_window(all.mlx.mlx_ptr, all.mlx.win_ptr, all.img.img_ptr, all.pos.x, all.pos.y);
			all.pos.y += img_height;
		}
		all.pos.x += img_width;
	}
	mlx_loop(all.mlx.mlx_ptr);
}
