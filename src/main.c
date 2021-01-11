/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:07:00 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/08 13:10:50 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error_put(int errno)
{
	if (errno == 1)
		ft_putstr_fd("Error\nWrong arguments!\n", 1);
	else if (errno == 2)
		ft_putstr_fd("Error\nInvalid syntax in second argument!\n", 1);
	else if (errno == 3)
		ft_putstr_fd("Error\nInvalid file format!\n", 1);
	else if (errno == 4)
		ft_putstr_fd("Error\nDescription file not found!\n", 1);
	else if (errno == 5)
		ft_putstr_fd("Error\nWrong information in description file!\n", 1);
	else if (errno == 6)
		ft_putstr_fd("Error\nMap description not found!\n", 1);
	else if (errno == 7)
		ft_putstr_fd("Error\nInvalid resolution param!\n", 1);
	else if (errno == 8)
		ft_putstr_fd("Error\nInvalid texture params!\n", 1);
	else if (errno == 9)
		ft_putstr_fd("Error\nInvalid color params!\n", 1);
	else if (errno == 10)
		ft_putstr_fd("Error\nInvalid map description!\n", 1);
	else if (errno == 11)
		ft_putstr_fd("Error\nWrong player position!\n", 1);
	else if (errno == 12)
		ft_putstr_fd("Error\nSomething failed successfully!\n", 1);
	exit(EXIT_FAILURE);
}

int		program_exit(t_all *all)
{
	mlx_destroy_window(all->mlx.ptr, all->win.ptr);
	system("leaks cub3D");
	exit(EXIT_SUCCESS);
	return (1);
}

int		main(int argc, char **argv)
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	if (argc < 2 || argc > 3)
		error_put(1);
	if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
		error_put(2);
	if (!ft_file_format_cmp(argv[1], ".cub"))
		error_put(3);
	config_parse(&all, argv[1]);
	if (!all.map_rows)
		error_put(6);
	sprite_init(&all, all.sprite_count);
	map_init(&all, argv[1]);
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		bitmap_save(&all);
	window_init(&all);
	return (1);
}
