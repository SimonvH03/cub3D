/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_elements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 16:58:42 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/19 20:22:36 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	load_tile_texture(
		t_window *window,
		mlx_texture_t **dest,
		const char *line)
{
	while (*line == ' ')
		++line;
	if (ft_strnstr(line, ".png", -1) != NULL)
	{
		*dest = mlx_load_png(line);
		if (*dest == NULL)
			return (set_error(CUB_MLXFAIL));
	}
	else if (ft_strnstr(line, ".xpm42", -1) != NULL)
	{
		*dest = modlx_load_xpm42(line);
		if (*dest == NULL)
			return (RETURN_FAILURE);
		if (transpose_texture(*dest) != RETURN_SUCCESS)
			return (RETURN_FAILURE);
		if (add_to_texture_list(window, *dest) != RETURN_SUCCESS)
			return (RETURN_FAILURE);
	}
	else
		return (set_error(CUB_INVTEX));
	return (RETURN_SUCCESS);
}

static int
	load_colour(
		uint32_t *dest,
		const char *line)
{
	t_colour_construct	new;
	int					r_val;
	int					g_val;
	int					b_val;
	int					a_val;

	while (*line == ' ')
		++line;
	a_val = 0xFF;
	r_val = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	g_val = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	b_val = ft_atoi(line);
	if (a_val < 0 || a_val > 255
		|| r_val < 0 || r_val > 255
		|| g_val < 0 || g_val > 255
		|| b_val < 0 || b_val > 255)
		return (set_error(CUB_INVCLR));
	new.a = a_val;
	new.r = r_val;
	new.g = g_val;
	new.b = b_val;
	*dest = (uint32_t)((new.a << 24) | (new.b << 16) | (new.g << 8) | new.r);
	return (RETURN_SUCCESS);
}

static int
	evaluate_line(
		t_window *window,
		t_scene *scene,
		const char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		&& load_tile_texture(window, &scene->walls.north, &((line)[3])))
		return (RETURN_FAILURE);
	else if (ft_strncmp(line, "EA ", 3) == 0
		&& load_tile_texture(window, &scene->walls.east, &((line)[3])))
		return (RETURN_FAILURE);
	else if (ft_strncmp(line, "SO ", 3) == 0
		&& load_tile_texture(window, &scene->walls.south, &((line)[3])))
		return (RETURN_FAILURE);
	else if (ft_strncmp(line, "WE ", 3) == 0
		&& load_tile_texture(window, &scene->walls.west, &((line)[3])))
		return (RETURN_FAILURE);
	else if (ft_strncmp(line, "F ", 2) == 0
		&& load_colour(&scene->floor_clr, &((line)[2])))
		return (RETURN_FAILURE);
	else if (ft_strncmp(line, "C ", 2) == 0
		&& load_colour(&scene->ceiling_clr, &((line)[2])))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

bool
	has_valid_type_identifier(
		const char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		return (true);
	return (false);
}

int
	read_elements(
		t_window *window,
		t_scene *scene,
		char ***content)
{
	int		element_count;
	char	*line;

	if (load_tile_texture(window, &scene->walls.doorface, DOORFACE_TEXTURE_PATH)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (load_tile_texture(window, &scene->walls.doorside, DOORSIDE_TEXTURE_PATH)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	element_count = 0;
	while (**content && element_count < 6)
	{
		line = *(*content)++;
		if (**content[0] == '\0')
			continue ;
		if (!has_valid_type_identifier(line))
			return (set_error(CUB_INVELEM));
		if (evaluate_line(window, scene, line) != RETURN_SUCCESS)
			return (RETURN_FAILURE);
		element_count++;
	}
	return (RETURN_SUCCESS);
}
