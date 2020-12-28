/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:24:57 by tsierra-          #+#    #+#             */
/*   Updated: 2020/12/28 13:36:49 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// Incluida en la libft
/*
int		ft_only_spaces_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}*/
// Incluida en color_utils.c
size_t	ft_strlen_only_color(char *str)
{
	size_t	l;
	size_t	i;

	l = 0;
	i = 0;
	while (str[l] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != 'F' && str[i] != 'C')
			l++;
		i++;
	}
	return (l);
}
// Incluida en color_utils.c
char	*ft_strtrim_color(char *str)
{
	char	*copy;
	size_t	l;
	size_t	i;

	i = 0;
	l = ft_strlen_only_color(str);
	if (!(copy = (char*)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	i = 0;
	l = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != 'F' && str[i] != 'C')
		{
			copy[l] = str[i];
			l++;
		}
		i++;
	}
	copy[l] = '\0';
	return (copy);
}
// Incluida en la libft
/*
size_t	ft_strlen_no_tab(char *str)
{
	size_t	l;
	size_t	i;

	l = 0;
	i = 0;
	while (str[l] != '\0')
	{
		if (str[i] != '\t')
			l++;
		i++;
	}
	return (l);
}

char	*ft_str_tab_rem(char *str)
{
	char	*copy;
	size_t	l;
	size_t	i;

	i = 0;
	l = ft_strlen_no_tab(str);
	if (!(copy = (char*)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	i = 0;
	l = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\t')
		{
			copy[l] = str[i];
			l++;
		}
		i++;
	}
	copy[l] = '\0';
	return (copy);
}*/
// Incluida en la libft
/*
int		ft_count_char_in_str(char *str, char c)
{
	int	i;
	int	counter;

	if (!str)
		return (0);
	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}*/
// Incluida en la libft
/*
int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}*/
// Incluida en la libft
/*
int		ft_is_color_range(int color)
{
	if (color >= 0 && color <= 255)
		return (1);
	return (0);
}*/
// Incluida en el libft
/*
int		ft_file_format_cmp(char *str, char *format)
{
	char	*format_str;
	int		l_str;
	int		l_format;

	l_str = ft_strlen(str);
	l_format = ft_strlen(format);
	format_str = &str[l_str - l_format];
	if (ft_strncmp(format, format_str, l_format))
		return (0);
	return (1);
}*/
// Incluida en la libft
/*
int		free_2d(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (1);
}*/
// Incluida en la libft
/*
int		ft_is_str_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}*/
// Incluida en la libft
/*
int		ft_is_valid_file(char *path)
{
	int	fd;

	fd = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
	{
		return (0);
	}
	close(fd);
	return (1);
}*/
// Incluida en parse_textures2.c
int		parse_north_texture(char *param, t_all *all)
{
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(8);
	all->tex[0].path = ft_strdup(param);
	all->control ^= 0x2;
//	printf("%s\n", all->tex[0].path);
	count++;
	return (1);
}
// Incluida en parse_textures2.c
int		parse_south_texture(char *param, t_all *all)
{
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(8);
	all->tex[1].path = ft_strdup(param);
	all->control ^= 0x4;
//	printf("%s\n", all->tex[1].path);
	count++;
	return (1);
}
// Incluida en parse_textures2.c
int		parse_east_texture(char *param, t_all *all)
{
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(8);
	all->tex[2].path = ft_strdup(param);
	all->control ^= 0x8;
//	printf("%s\n", all->tex[2].path);
	count++;
	return (1);
}
//Incluida en parse_textures2.c
int		parse_west_texture(char *param, t_all *all)
{
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(8);
	all->tex[3].path = ft_strdup(param);
	all->control ^= 0x10;
//	printf("%s\n", all->tex[3].path);
	count++;
	return (1);
}
// Incluida en parse_textures2.c
int		parse_sprite_texture(char *param, t_all *all)
{
//	t_tex		tex;
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
		error_put(8);
	all->tex[4].path = ft_strdup(param);
	all->control ^= 0x20;
//	printf("%s\n", all->tex[4].path);
	count++;
	return (1);
}
// Incluida en parse_color_utils.c
int		rgb_to_hex(unsigned r, unsigned g, unsigned b)
{
	int	color;
	color = r & 0xFF;
	color <<= 8;
	color |= g & 0xFF;
	color <<= 8;
	color |= b & 0xFF;
	return (color);
}
// Incluida en parse_color.c
int		parse_floor_color(char **colors, t_all *all)
{
	t_color		color;
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
	{
		error_put(9);
	//	ft_putstr_fd("Error\nToo many floor color arguments\n", 1);
	//	exit(0);
	}
	color.r = ft_atoi(colors[0]);
	color.g = ft_atoi(colors[1]);
	color.b = ft_atoi(colors[2]);
	if (!ft_is_color_range(color.r) || !ft_is_color_range(color.g) ||
		!ft_is_color_range(color.b))
	{
		error_put(9);
	//	ft_putstr_fd("Error\nInvalid color values of floor\n", 1);
	//	exit(0);
	}
	all->draw.f_rgb = rgb_to_hex(color.r, color.g, color.b);
	all->control ^= 0x40;
//	printf("F r=%i g=%i b=%i\n", tex.f_red, tex.f_green, tex.f_blue);
	count++;
	return (1);
}
// Inclida en parse_color.c
int		parse_ceilling_color(char **colors, t_all *all)
{
	t_color		color;
	static int	count;

	if (!count)
		count = 0;
	if (count > 0)
	{
		error_put(9);
	//	ft_putstr_fd("Error\nToo many ceilling color arguments\n", 1);
	//	exit(0);
	}
	color.r = ft_atoi(colors[0]);
	color.g = ft_atoi(colors[1]);
	color.b = ft_atoi(colors[2]);
	if (!ft_is_color_range(color.r) || !ft_is_color_range(color.g) ||
		!ft_is_color_range(color.b))
	{
		error_put(9);
	//	ft_putstr_fd("Error\nInvalid color values of ceilling\n", 1);
	//	exit(0);
	}
	all->draw.c_rgb = rgb_to_hex(color.r, color.g, color.b);
	all->control ^= 0x80;
//	printf("C r=%i g=%i b=%i\n", tex.c_red, tex.c_green, tex.c_blue);
	count++;
	return (1);
}
// Inclluida en parse_params2.c
int		parse_resolution(char **params, t_all *all)
{
//	t_win	win;
	if (!ft_is_str_digit(params[1]) || !ft_is_str_digit(params[2])|| params[3]
		|| !(all->win.width = ft_atoi(params[1])) || !(all->win.height = ft_atoi(params[2])))
	{
		error_put(7);
	//	ft_putstr_fd("Error\nInvalid resolution arguments\n", 1);
	//	exit(0);
	}
	all->win.width = (all->win.width > 2560) ? 2560 : all->win.width;
	all->win.height = (all->win.height > 1395) ? 1395 : all->win.height;
	all->control ^= 0x1;
//	printf("%i %i\n", all->win.width, all->win.height);
	return (1);
}
// Incluida en parse_params.c
int		parse_textures(char **params, t_all *all)
{
	if (params[2] || !params[1])
	{
		error_put(8);
	//	ft_putstr_fd("Error\nInvalid texture arguments\n", 1);
	//	exit(0);
	}
	if ((!ft_file_format_cmp(params[1], ".xpm") 
			&& !ft_file_format_cmp(params[1], ".png")) 
			|| !ft_is_valid_file(params[1]))
	{
		error_put(8);
	//	ft_putstr_fd("Error\nInvalid texture file\n", 1);
	//	exit(0);
	}
	if (ft_memcmp(params[0], "NO", 2) == 0)
		parse_north_texture(params[1], all);
	else if (ft_memcmp(params[0], "SO", 2) == 0)
		parse_south_texture(params[1], all);
	else if (ft_memcmp(params[0], "WE", 2) == 0)
		parse_west_texture(params[1], all);
	else if (ft_memcmp(params[0], "EA", 2) == 0)
		parse_east_texture(params[1], all);
	else if (ft_memcmp(params[0], "S", 1) == 0)
		parse_sprite_texture(params[1], all);
	return (1);
}
// Incluida en parse_color.c
int		parse_color(char *params, t_all *all)
{
	char	**colors;

	if (!ft_memchr(params, ',', ft_strlen(params)) ||
			ft_count_char_in_str(params, ',') != 2)
	{
		error_put(9);
	//	ft_putstr_fd("Error\nInvalid color arguments\n", 1);
	//	exit(0);
	}
	colors = ft_split(params, ',');
	if (colors[3] || !colors[2])
	{
		free_2d(colors);
		error_put(9);
	//	ft_putstr_fd("Error\nInvalid color arguments 2\n", 1);
	//	exit(0);
	}
	if (!ft_is_str_digit(colors[0]) || !ft_is_str_digit(colors[1]) ||
		!ft_is_str_digit(colors[2]))
	{
		free_2d(colors);
		error_put(9);
	//	ft_putstr_fd("Error\nInvalid color number\n", 1);
	//	exit(0);
	}
	if (all->f_c == 1)
		parse_floor_color(colors, all);
	else if (all->f_c == 0)
		parse_ceilling_color(colors, all);
	free_2d(colors);
	return (1);
}
// Incluida en parse_params.c
int		parse_params(char **params, t_all *all)
{
	if (!ft_strcmp(params[0], "R"))
		parse_resolution(params, all);
	else if (!ft_strcmp(params[0], "NO") || !ft_strcmp(params[0], "SO") ||
		!ft_strcmp(params[0], "WE") || !ft_strcmp(params[0], "EA") ||
		!ft_strcmp(params[0], "S"))
		parse_textures(params, all);
	else
	{
		error_put(5);
	//	ft_putstr_fd("Error\nInvalid info in description file\n", 1);
	//	exit(0);
	}
	return (1);
}
// incluida en parse_map_utils.c
int		valid_first_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}
// incluida en parse_map_utils.c
int		ft_is_surrounded(t_all *all, int x, int y)
{
	if (all->map[x - 1][y - 1] == ' ' || all->map[x - 1][y - 1] == '\0' ||
			all->map[x - 1][y] == ' ' || all->map[x - 1][y] == '\0' ||
			all->map[x - 1][y + 1] == ' ' || all->map[x - 1][y + 1] == '\0' ||
			all->map[x][y - 1] == ' ' || all->map[x][y - 1] == '\0' ||
			all->map[x][y + 1] == ' ' || all->map[x][y + 1] == '\0' ||
			all->map[x + 1][y - 1] == ' ' || all->map[x + 1][y - 1] == '\0' ||
			all->map[x + 1][y] == ' ' || all->map[x + 1][y] == '\0' ||
			all->map[x + 1][y + 1] == ' ' || all->map[x + 1][y + 1] == '\0')
	{
		error_put(10);
//		ft_putstr_fd("Error\nInvalid open map\n", 1);
//		exit(0);
	}
	return (1);
}

void	direction_control(t_all *all, double x, double y)
{
	all->dir.x = x;
	all->dir.y = y;
}

void	plane_control(t_all *all, double x, double y)
{
	all->plane.x = x;
	all->plane.y = y;
}

void	player_control(t_all *all, int row, int column)
{
	all->control_player++;
	if (all->control_player > 1)
		error_put(11);
	all->pos.x = (double)row + 0.5;
	all->pos.y = (double)column + 0.5;
	if (all->map[row][column] == 'N')
	{
		direction_control(all, -1, 0);
		plane_control(all, 0, 0.66);
	}
	else if (all->map[row][column] == 'S')
	{
		direction_control(all, 1, 0);
		plane_control(all, 0, -0.66);
	}
	else if (all->map[row][column] == 'W')
	{
		direction_control(all, 0, -1);
		plane_control(all, -0.66, 0);
	}
	else if (all->map[row][column] == 'E')
	{
		direction_control(all, 0, 1);
		plane_control(all, 0.66, 0);
	}
}

void	sprite_control(t_all *all, int row, int column)
{
	all->sprite[all->sprite_count].x = (double)row + 0.5;
	all->sprite[all->sprite_count].y = (double)column + 0.5;
//	printf("sprite_count=%d\nXsprite=%f\nYsprite=%f\n", all->sprite_count, all->sprite[all->sprite_count].x, all->sprite[all->sprite_count].y);
	all->sprite_count++;
}

void	sprite_init(t_all *all, int count)
{
	if (!(all->sprite = (t_dvec*)malloc(count * sizeof(t_dvec))))
		error_put(12);
	if (!(all->sprite_order = (int*)malloc(count * sizeof(int))))
		error_put(12);
	if (!(all->sprite_dist = (double*)malloc(count * sizeof(double))))
		error_put(12);
}

// Incluida en parse_map.c
int		is_valid_map(t_all *all)
{
	int	i;
	int	j;

	if (!valid_first_line(all->map[0]))
	{
		error_put(10);
	//	ft_putstr_fd("Error\nInvalid open map 2\n", 1);
	//	exit(0);
	}
	all->control_player = 0;
	all->sprite_count = 0;
	i = 0;
	while (i < all->map_rows)
	{
		j = 0;
		while (all->map[i][j] != '\0')
		{
			if (all->map[i][j] != ' ' && all->map[i][j] != '1')
				ft_is_surrounded(all, i, j);
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
	{
		error_put(11);
	//	ft_putstr_fd("Error\nNone player position\n", 1);
	//	exit(0);
	}
//	if (all->control_player > 1)
//	{
//		error_put(11);
	//	ft_putstr_fd("Error\nToo many player positions\n", 1);
	//	exit(0);
//	}
	return (1);
}
// incluida en parse_map.c
int		create_maze(char *line, t_all *all)
{
	int		i;
	char 	*tmp;

	i = 0;
	tmp = line;
	while (line[i])
	{
		all->map[all->rows][i] = tmp[i];
	//	printf("rows=%d\ncolumn=%d\n", all->rows, i);
		i++;
	}
	all->map[all->rows][i] = '\0';
//	printf("%s\n", all->map[all->rows]);
	all->is_map = 1;
	all->rows++;
	return (1);
}
// Incluida en parse_map.c
int		skip_params(char *line, t_all *all)
{
	if ((line[0] == '\0' || ft_only_spaces_line(line)) && !all->is_map)
		return (1);	
	else if (all->control == 8)
		create_maze(line, all);
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
// Incluida en parse_map.c
int		init_map(t_all *all, char *argv)
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
	all->rows = 0;
	all->control = 0;
	all->is_map = 0;
	fd = open(argv, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		skip_params(line, all);
		free(line);
	}
	free(line);
	close(fd);
	is_valid_map(all);
	return (1);
}
// Incluida en parse_params2.c
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
//	printf("%s\n", line);
	return (1);
}
// Incluida en parse_color.c
int		parse_pre_color(char *params, t_all *all)
{
	char	*tmp;

	if (ft_memchr(params, 'F', ft_strlen(params)) && 
			ft_memchr(params, 'C', ft_strlen(params)))
	{
		error_put(9);
//		ft_putstr_fd("Error\nInvalid color arguments 3\n", 1);
//		exit(0);
	}
	if (ft_memchr(params, 'F', ft_strlen(params)))
		all->f_c = 1;
	else
		all->f_c = 0;
	tmp = ft_strtrim_color(params);
	if (ft_count_char_in_str(tmp, ',') != 2)
	{
		free(tmp);
		error_put(9);
//		ft_putstr_fd("Error\nInvalid color arguments 4\n", 1);
//		exit(0);
	}
	parse_color(tmp, all);
	free(tmp);
	return (1);
}
// Incluida en parse_params.c
int		parse_line(char *line, t_all *all)
{
	char	**params;
	char	*tmp;
	char	*tmp2;

	if ((line[0] == '\0' || ft_only_spaces_line(line)) && !all->map_rows)
		return (1);
	else if ((line[0] == '1' || line[0] == ' ' || line[0] == '\0' ||
				line[0] == '\t') && all->control == 0xFF)
		is_map(line, all);
	else
	{
		tmp = ft_str_tab_rem(line);
		tmp2 = ft_strtrim(tmp, " ");
		free(tmp);
		if (!ft_memcmp(tmp2, "F ", 2) || !ft_memcmp(tmp2, "C ", 2))
		{
			parse_pre_color(tmp2, all);
			free(tmp2);
			return(1);
		}
		params = ft_split(tmp2, ' ');
		free(tmp2);
		parse_params(params, all);
		free_2d(params);
	}
	return (1);
}
/*
void	struct_init(t_all *all)
{
	all->win_ptr = 0;
	all->win.width = 0;
	all->win.height = 0;
	all->img.ptr = 0;
	all->img.buffer = NULL;
	all->img.bits_per_pixel = 0;
	all->img.size_line = 0;
	all->img.endian = 0;
	all->mlx_ptr = 0;
	all->maze.x = 0;
	all->maze.y = 0;
	all->pos.x = 0;
	all->pos.y = 0;
	all->dir.x = 0;
	all->dir.y = 0;
	all->plane.x = 0;
	all->plane.y = 0;
	all->ray.r = 0;
	all->ray.cam.x = 0;
	all->ray.delta.x = 0;
	all->ray.delta.y = 0;
	all->ray.dir.x = 0;
	all->ray.dir.y = 0;
	all->ray.step.x = 0;
	all->ray.step.y = 0;
	all->ray.side.dist.x = 0;
	all->ray.side.dist.y = 0;
	all->ray.wall.hit = 0;
	all->ray.wall.side = 0;
	all->ray.wall.dist = 0;
	all->draw.height = 0;
	all->draw.start = 0;
	all->draw.end = 0;
	all->color = 0;
}
*/
// Incluida en main.c
int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		out;
	t_all	all;

	fd = 0;
	line = NULL;
	out = 1;
//	if (!(all = (t_all*)malloc(sizeof(t_all))))
//		return (0);
	ft_bzero(&all, sizeof(t_all));
//	all.control = 0;
//	all.map_rows = 0;
//	all.f_c = 0;
	if (argc < 2 || argc > 3)
	{
		error_put(1);
	//	ft_putstr_fd("Error\nInvalid arguments\n", 1);
	//	exit(0);
	}
	if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
	{
		error_put(2);
	//	ft_putstr_fd("Error\nInvalid second argument\n", 1);
	//	exit(0);
	}	
	if(!ft_file_format_cmp(argv[1], ".cub"))
	{
		error_put(3);
	//	ft_putstr_fd("Error\nInvalid format of map file\n", 1);
	//	exit(0);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		error_put(4);
	//	ft_putstr_fd("Error\nDescription file not found\n", 1);
	//	exit(0);
	}
//	struct_init(&all);
	while ((out = get_next_line(fd, &line)) == 1)
	{
		parse_line(line, &all);
		free(line);
	}
	parse_line(line, &all);
	free(line);
	close(fd);
	if (!all.map_rows)
	{
		error_put(6);
	//	ft_putstr_fd("Error\nNone map area\n", 1);
	//	exit(0);
	}
//	printf("%i\n", all.control);
//	printf("%i\n", all.map_rows);
//	printf("%i\n", all.map_columns);
//	printf("%s\n", all.tex[4].path);
	sprite_init(&all, all.sprite_count);
	init_map(&all, argv[1]);
//	printf("%d\n", all.sprite_count);
	window_init(&all);
//	all->mlx_ptr = mlx_init();
//	all->win_ptr = mlx_new_window(all->mlx_ptr, all->win.width, all->win.height, "cub3D");
//	printf("%i %i\n", all->win.width, all->win.height);
//	all->img.ptr = mlx_new_image(all->mlx_ptr, all->win.width, all->win.height);
//	all->img.buffer = mlx_get_data_addr(all->img.ptr, &all->img.bits_per_pixel, &all->img.size_line, &all->img.endian);
//	screen_draw(all);
//	mlx_put_image_to_window(all->mlx_ptr, all->win_ptr, all->img.ptr, 0, 0);
//	mlx_hook(all->win_ptr, 2, 0, &key_press, &all);
//	mlx_loop_hook(all->mlx_ptr, &display, all);
//	mlx_loop(all->mlx_ptr);
	system("leaks cub3D");
	return (1);
}

// Crear una funtion de errores
// Crear una funtion de liberar memoria
