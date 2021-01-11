/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:22:54 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/08 13:25:19 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		north_texture_parse(char *param, t_all *all)
{
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(8);
	all->tex[0].path = ft_strdup(param);
	all->control ^= 0x2;
	count++;
	return (1);
}

int		south_texture_parse(char *param, t_all *all)
{
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(8);
	all->tex[1].path = ft_strdup(param);
	all->control ^= 0x4;
	count++;
	return (1);
}

int		east_texture_parse(char *param, t_all *all)
{
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(8);
	all->tex[2].path = ft_strdup(param);
	all->control ^= 0x8;
	count++;
	return (1);
}

int		west_texture_parse(char *param, t_all *all)
{
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(8);
	all->tex[3].path = ft_strdup(param);
	all->control ^= 0x10;
	count++;
	return (1);
}

int		sprite_texture_parse(char *param, t_all *all)
{
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(8);
	all->tex[4].path = ft_strdup(param);
	all->control ^= 0x20;
	count++;
	return (1);
}
