/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:14:02 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/22 16:21:23 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	sprite_raycast(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->sprite_count)
	{
		all->sprite_order[i] = i;
		all->sprite_dist[i] = pow(all->pos.x - all->sprite[i].x, 2) + pow(all->pos.y - all->sprite[i].y, 2);
		i++;
	}
}
