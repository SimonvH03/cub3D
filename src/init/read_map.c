/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 16:58:42 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/21 22:38:15 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	tilemap_interpret_cell(
		t_grid *grid,
		int16_t *dest,
		int token)
{
	if (!ft_strchr(VALID_MAP_CHAR, token) && token != '\0')
	{
		return (set_error(CUB_INVMAP));
	}
	else if (ft_isdigit(token))
	{
		*dest = set_tilemap_cell((token > '0'), (token - '0'), token);
	}
	else
	{
		if (token == 'd' || token == 'D')
			*dest = set_tilemap_cell(true, grid->door_count++, token);
		else
			*dest = set_tilemap_cell(true, 0, token);
	}
	return (RETURN_SUCCESS);
}

static int
	tilemap_interpret_row(
		t_grid *grid,
		const int y,
		const char *line)
{
	unsigned int	x;

	x = 0;
	while (line[x])
	{
		if (tilemap_interpret_cell(grid, &grid->tilemap[y][x], line[x])
			!= RETURN_SUCCESS)
			return (RETURN_FAILURE);
		++x;
	}
	while (x < grid->x_max)
	{
		if (tilemap_interpret_cell(grid, &grid->tilemap[y][x], ' ')
			!= RETURN_SUCCESS)
			return (RETURN_FAILURE);
		++x;
	}
	return (RETURN_SUCCESS);
}

static int
	tilemap_size(
		t_grid *grid,
		char *const *content)
{
	int	x;
	int	y;
	int	max_x;

	x = 0;
	y = 0;
	max_x = 0;
	while (content[y])
	{
		x = ft_strlen(content[y]);
		if (x > max_x)
			max_x = x;
		++y;
	}
	grid->x_max = max_x;
	grid->y_max = y;
	if (grid->x_max == 0 || grid->y_max == 0)
		return (set_error(CUB_NOMAP));
	return (RETURN_SUCCESS);
}

int
	read_tilemap(
		t_grid *grid,
		char *const *content)
{
	unsigned int	y;

	if (tilemap_size(grid, content) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	grid->tilemap = (int16_t **)ft_calloc(grid->y_max + 1, sizeof(int16_t *));
	if (grid->tilemap == NULL)
		return (set_error(CUB_MEMFAIL));
	grid->tilemap[grid->y_max] = NULL;
	y = 0;
	while (y < grid->y_max)
	{
		grid->tilemap[y] = (int16_t *)ft_calloc(grid->x_max, sizeof(int16_t));
		if (grid->tilemap[y] == NULL)
			return (set_error(CUB_MEMFAIL));
		if (tilemap_interpret_row(grid, y, content[y]) != RETURN_SUCCESS)
			return (RETURN_FAILURE);
		++y;
	}
	return (RETURN_SUCCESS);
}
