/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:56:53 by tsierra-          #+#    #+#             */
/*   Updated: 2021/01/08 13:05:43 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		textures_parse(char **params, t_all *all)
{
	if (params[2] || !params[1])
		error_put(8);
	if ((!ft_file_format_cmp(params[1], ".xpm")
		&& !ft_file_format_cmp(params[1], ".png"))
		|| !ft_is_valid_file(params[1]))
		error_put(8);
	if (ft_memcmp(params[0], "NO", 2) == 0)
		north_texture_parse(params[1], all);
	else if (ft_memcmp(params[0], "SO", 2) == 0)
		south_texture_parse(params[1], all);
	else if (ft_memcmp(params[0], "WE", 2) == 0)
		west_texture_parse(params[1], all);
	else if (ft_memcmp(params[0], "EA", 2) == 0)
		east_texture_parse(params[1], all);
	else if (ft_memcmp(params[0], "S", 1) == 0)
		sprite_texture_parse(params[1], all);
	return (1);
}

int		params_parse(char **params, t_all *all)
{
	if (!ft_strcmp(params[0], "R"))
		resolution_parse(params, all);
	else if (!ft_strcmp(params[0], "NO") || !ft_strcmp(params[0], "SO") ||
		!ft_strcmp(params[0], "WE") || !ft_strcmp(params[0], "EA") ||
		!ft_strcmp(params[0], "S"))
		textures_parse(params, all);
	else
		error_put(5);
	return (1);
}

int		line_parse(char *line, t_all *all)
{
	char	**params;
	char	*tmp;
	char	*tmp2;

	tmp = ft_str_tab_remove(line);
	tmp2 = ft_strtrim(tmp, " ");
	free(tmp);
	if (!ft_memcmp(tmp2, "F ", 2) || !ft_memcmp(tmp2, "C ", 2))
	{
		color_pre_parse(tmp2, all);
		free(tmp2);
		return (1);
	}
	params = ft_split(tmp2, ' ');
	free(tmp2);
	params_parse(params, all);
	free_2d(params);
	return (1);
}

int		line_pre_parse(char *line, t_all *all)
{
	if ((line[0] == '\0' || ft_only_spaces_line(line)) && !all->map_rows)
		return (1);
	else if ((line[0] == '1' || line[0] == ' ' || line[0] == '\0' ||
				line[0] == '\t') && all->control == 0xFF)
		is_map(line, all);
	else
		line_parse(line, all);
	return (1);
}

int		config_parse(t_all *all, char *path)
{
	int		fd;
	char	*line;
	int		out;

	fd = 0;
	line = NULL;
	out = 1;
	if ((fd = open(path, O_RDONLY)) < 0)
		error_put(4);
	while ((out = get_next_line(fd, &line)) == 1)
	{
		line_pre_parse(line, all);
		free(line);
	}
	line_pre_parse(line, all);
	free(line);
	close(fd);
	return (1);
}
