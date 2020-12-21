/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:50:52 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/16 12:21:25 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		program_exit(t_all *all)
{
	mlx_destroy_window(all->mlx.ptr, all->win.ptr);
	system("leaks cub3D");
	exit(EXIT_SUCCESS);
	return (1);
}


void	error_put(int errno)
{
//	clear_memory();
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
	system("leaks cub3D");
	exit(EXIT_FAILURE);
}

/*
**	int	main(int argc, char **argv)
**	{
**		return (0);
**	}
*/
