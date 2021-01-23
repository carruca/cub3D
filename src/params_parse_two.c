/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:27:05 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/23 18:45:07 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		is_map(char *line, t_all *all)
{
	int		i;

	i = 0;
	if (line[0] == '\0')
		all->map_rows++;
	else
	{
		while (line[i] != '\0')
		{
			if (line[i] != ' ' && line[i] != '0' && line[i] != '1' &&
					line[i] != '2' && line[i] != 'N' && line[i] != 'S'
					&& line[i] != 'E' && line[i] != 'W' && line[i] != '\t')
				error_put(10);
			else if (line[i] == '2')
				all->sprite_count++;
			i++;
		}
		i = ft_strlen(line);
		if (all->map_columns < i)
			all->map_columns = i;
		all->map_rows++;
	}
	return (1);
}

int		resolution_parse(char **params, t_all *all)
{
	if (!ft_is_str_digit(params[1]) || !ft_is_str_digit(params[2])
			|| params[3])
		error_put(7);
	all->win.width = ft_atoi(params[1]);
	all->win.height = ft_atoi(params[2]);
	if (all->win.width < 1 || all->win.height < 1)
		error_put(7);
	all->win.width = (all->win.width > 2560) ? 2560 : all->win.width;
	all->win.height = (all->win.height > 1395) ? 1395 : all->win.height;
	all->control ^= 0x1;
	return (1);
}
