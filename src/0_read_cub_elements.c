/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_read_cub_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/15 19:23:10 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	load_texture(
		mlx_texture_t **dest,
		char *line)
{
	xpm_t	*tempx;

	while (*line == ' ')
		++line;
	if (ft_strnstr(line, ".png", -1) != NULL)
	{
		*dest = mlx_load_png(line);
		if (*dest == NULL)
			error_exit(mlx_errno, 0, "failed to load .png file from scene");
	}
	else if (ft_strnstr(line, ".xpm42", -1) != NULL)
	{
		tempx = mlx_load_xpm42(line);
		if (tempx == NULL)
			error_exit(mlx_errno, 0, "failed to load .xpm42 file from scene");
		*dest = &tempx->texture;
	}
	else
		error_exit(0, EINVAL, "Only .png or .xpm42 textures in scene svp");
}

static void
	load_colour(
		uint32_t *dest,
		char *line)
{
	t_colour_construct	new;

	while (*line == ' ')
		++line;
	new.a = 0xFF;
	new.r = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	new.g = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	new.b = ft_atoi(line);
	*dest = (uint32_t)((new.r << 24) | (new.g << 16) | (new.b << 8) | new.a);
}

void
	read_elements(
		t_scene *scene)
{
	int	element_count;

	element_count = 0;
	while (*scene->content && element_count++ < 6)
	{
		if (ft_strncmp(*scene->content, "NO ", 3) == 0)
			load_texture(&scene->north_texture, *scene->content + 3);
		else if (ft_strncmp(*scene->content, "EA ", 3) == 0)
			load_texture(&scene->east_texture, *scene->content + 3);
		else if (ft_strncmp(*scene->content, "SO ", 3) == 0)
			load_texture(&scene->south_texture, *scene->content + 3);
		else if (ft_strncmp(*scene->content, "WE ", 3) == 0)
			load_texture(&scene->west_texture, *scene->content + 3);
		else if (ft_strncmp(*scene->content, "F ", 2) == 0)
			load_colour(&scene->floor, *scene->content + 2);
		else if (ft_strncmp(*scene->content, "C ", 2) == 0)
			load_colour(&scene->ceiling, *scene->content + 2);
		else if (*scene->content[0] != '\0')
			error_exit(0, EINVAL, "missing or invalid scene.cub elements");
		else
			--element_count;
		++scene->content;
	}
}

short
	get_content(
		t_scene *scene)
{
	char	*buffer;
	int		fd;

	fd = open(scene->name, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	buffer = get_next_line(fd);
	if (buffer == NULL)
		return (EXIT_FAILURE);
	scene->content = NULL;
	while (buffer != NULL)
	{
		if (buffer[0] != '\n')
		{
			buffer[ft_strlen(buffer) - 1] = '\0';
			scene->content = ft_array_append(scene->content, buffer);
		}
		else
			free(buffer);
		buffer = get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}
