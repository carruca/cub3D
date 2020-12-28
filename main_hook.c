/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:26:31 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/28 13:37:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	printf("%i\n", keycode);
}

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	printf("button=%i x=%i y=%i\n", button, x, y);
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit (-1);
	}
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit (0);
}

int	key_release(int keycode, t_mlx *mlx)
{
	printf("something\n");
}

int	mouse_move(int button, int x, int y, t_mlx *mlx)
{

	printf("Hello!\n");
}

int	main()
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 640, 480, "Hello!");
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_mouse_hook(mlx.win_ptr, mouse_hook, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1L<<0, key_press, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L<<17, close_window, &mlx);
	mlx_hook(mlx.win_ptr, 3, 1L<<1, key_release, &mlx);
	mlx_hook(mlx.win_ptr, 6, 1L<<6, mouse_move, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

/*
 * Esc: 53 key
 *
 */
