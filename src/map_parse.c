/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:31:32 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/08 14:00:44 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		is_surrounded(t_all *all, int x, int y)
{
	if (all->map[x - 1][y - 1] == ' ' || all->map[x - 1][y - 1] == '\0' ||
			all->map[x - 1][y] == ' ' || all->map[x - 1][y] == '\0' ||
			all->map[x - 1][y + 1] == ' ' || all->map[x - 1][y + 1] == '\0' ||
			all->map[x][y - 1] == ' ' || all->map[x][y - 1] == '\0' ||
			all->map[x][y + 1] == ' ' || all->map[x][y + 1] == '\0' ||
			all->map[x + 1][y - 1] == ' ' || all->map[x + 1][y - 1] == '\0' ||
			all->map[x + 1][y] == ' ' || all->map[x + 1][y] == '\0' ||
			all->map[x + 1][y + 1] == ' ' || all->map[x + 1][y + 1] == '\0')
		error_put(10);
	return (1);
}

void	is_valid_map(t_all *all)
{
	int	i;
	int	j;

	if (!valid_first_line(all->map[0]))
		error_put(10);
	all->sprite_count = 0;
	i = 0;
	while (i < all->map_rows)
	{
		j = 0;
		while (all->map[i][j] != '\0')
		{
			if (all->map[i][j] != ' ' && all->map[i][j] != '1')
				is_surrounded(all, i, j);
			if (all->map[i][j] == 'N' || all->map[i][j] == 'S' ||
					all->map[i][j] == 'W' || all->map[i][j] == 'E')
				player_control(all, i, j);
			if (all->map[i][j] == '2')
				sprite_control(all, i, j);
			j++;
		}
		i++;
	}
	if (!all->control_player)
		error_put(11);
}

int		map_create(char *line, t_all *all)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = line;
	while (line[i])
	{
		all->map[all->rows][i] = tmp[i];
		i++;
	}
	all->map[all->rows][i] = '\0';
	all->is_map = 1;
	all->rows++;
	return (1);
}

int		map_parse(char *line, t_all *all)
{
	if ((line[0] == '\0' || ft_only_spaces_line(line)) && !all->is_map)
		return (1);
	else if (all->control == 8)
		map_create(line, all);
	else if (ft_strchr(line, 'R'))
		all->control++;
	else if (ft_strchr(line, 'N') && ft_strchr(line, 'O'))
		all->control++;
	else if (ft_strchr(line, 'S') && ft_strchr(line, 'O'))
		all->control++;
	else if (ft_strchr(line, 'W') && ft_strchr(line, 'E'))
		all->control++;
	else if (ft_strchr(line, 'E') && ft_strchr(line, 'A'))
		all->control++;
	else if (ft_strchr(line, 'S') && !ft_strchr(line, '1'))
		all->control++;
	else if (ft_strchr(line, 'F'))
		all->control++;
	else if (ft_strchr(line, 'C'))
		all->control++;
	return (1);
}

int		map_init(t_all *all, char *path)
{
	int		fd;
	int		i;
	char	*line;

	if (!(all->map = (char**)malloc(all->map_rows * sizeof(char*))))
		return (0);
	i = 0;
	while (i < all->map_rows)
	{
		all->map[i] = (char*)malloc(all->map_columns * sizeof(char));
		i++;
	}
	all->control = 0;
	fd = open(path, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		map_parse(line, all);
		free(line);
	}
	free(line);
	close(fd);
	is_valid_map(all);
	return (1);
}
