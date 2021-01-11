/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:11:26 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/08 13:17:03 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		color_rgb_to_hex(unsigned r, unsigned g, unsigned b)
{
	int	color;

	color = r & 0xFF;
	color <<= 8;
	color |= g & 0xFF;
	color <<= 8;
	color |= b & 0xFF;
	return (color);
}

int		color_floor_parse(char **colors, t_all *all)
{
	t_color		color;
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(9);
	color.r = ft_atoi(colors[0]);
	color.g = ft_atoi(colors[1]);
	color.b = ft_atoi(colors[2]);
	if (!ft_is_color_range(color.r) || !ft_is_color_range(color.g) ||
		!ft_is_color_range(color.b))
		error_put(9);
	all->draw.f_rgb = color_rgb_to_hex(color.r, color.g, color.b);
	all->control ^= 0x40;
	count++;
	return (1);
}

int		color_ceilling_parse(char **colors, t_all *all)
{
	t_color		color;
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(9);
	color.r = ft_atoi(colors[0]);
	color.g = ft_atoi(colors[1]);
	color.b = ft_atoi(colors[2]);
	if (!ft_is_color_range(color.r) || !ft_is_color_range(color.g) ||
		!ft_is_color_range(color.b))
		error_put(9);
	all->draw.c_rgb = color_rgb_to_hex(color.r, color.g, color.b);
	all->control ^= 0x80;
	count++;
	return (1);
}

int		color_parse(char *params, t_all *all)
{
	char	**colors;

	if (!ft_memchr(params, ',', ft_strlen(params)) ||
			ft_count_char_in_str(params, ',') != 2)
		error_put(9);
	colors = ft_split(params, ',');
	if (colors[3] || !colors[2])
	{
		free_2d(colors);
		error_put(9);
	}
	if (!ft_is_str_digit(colors[0]) || !ft_is_str_digit(colors[1]) ||
		!ft_is_str_digit(colors[2]))
	{
		free_2d(colors);
		error_put(9);
	}
	if (all->f_c == 1)
		color_floor_parse(colors, all);
	else if (all->f_c == 0)
		color_ceilling_parse(colors, all);
	free_2d(colors);
	return (1);
}

int		color_pre_parse(char *params, t_all *all)
{
	char	*tmp;

	if (ft_memchr(params, 'F', ft_strlen(params)) &&
		ft_memchr(params, 'C', ft_strlen(params)))
		error_put(9);
	if (ft_memchr(params, 'F', ft_strlen(params)))
		all->f_c = 1;
	else
		all->f_c = 0;
	tmp = ft_strtrim_color(params);
	if (ft_count_char_in_str(tmp, ',') != 2)
	{
		free(tmp);
		error_put(9);
	}
	color_parse(tmp, all);
	free(tmp);
	return (1);
}
