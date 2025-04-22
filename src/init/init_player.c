/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/22 02:03:12 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	init_movement_matrix(
		t_camera *camera)
{
	camera->movement_matrix[0][0] = -1 / sqrtf(2);
	camera->movement_matrix[0][1] = 0;
	camera->movement_matrix[0][2] = 1 / sqrtf(2);
	camera->movement_matrix[1][0] = -1;
	camera->movement_matrix[1][1] = 0;
	camera->movement_matrix[1][2] = 1;
	camera->movement_matrix[2][0] = -1 / sqrtf(2);
	camera->movement_matrix[2][1] = 0;
	camera->movement_matrix[2][2] = 1 / sqrtf(2);
}

static void
	init_camera(
		t_camera *camera,
		const int pos_y,
		const int pos_x,
		const char cardinal)
{
	camera->pos_y = pos_y + 0.5;
	camera->pos_x = pos_x + 0.5;
	camera->dir_x = 0;
	camera->dir_y = 0;
	if (cardinal == 'N')
		camera->dir_y = -1;
	if (cardinal == 'E')
		camera->dir_x = 1;
	if (cardinal == 'S')
		camera->dir_y = 1;
	if (cardinal == 'W')
		camera->dir_x = -1;
	camera->plane_x = CAMERA_PLANE * camera->aspect_ratio * -camera->dir_y;
	camera->plane_y = CAMERA_PLANE * camera->aspect_ratio * camera->dir_x;
	camera->movement_speed = MOVEMENT_SPEED;
	camera->rotation_cosin[0] = cos(ROTATION_SPEED);
	camera->rotation_cosin[1] = sin(ROTATION_SPEED);
	init_movement_matrix(camera);
}

static int
	find_starting_position(
		t_grid *grid,
		unsigned int y,
		unsigned int x,
		void *param)
{
	int		*starting_positions;
	int16_t	cell;

	starting_positions = param;
	cell = grid->tilemap[y][x];
	if (ft_strchr("NESW", get_type(cell)) && get_type(cell) != 0)
	{
		if (++(*starting_positions) > 1)
			return (set_error(CUB_MULTPLAY));
	}
	return (RETURN_SUCCESS);
}

// never fails
// !! replaces player position with floor tile
static int
	put_camera(
		t_grid *grid,
		unsigned int y,
		unsigned int x,
		void *param)
{
	t_camera	*camera;
	int16_t		cell;

	camera = param;
	cell = grid->tilemap[y][x];
	if (ft_strchr("NESW", get_type(cell)) && get_type(cell) != 0)
	{
		init_camera(camera, y, x, get_type(cell));
		grid->tilemap[y][x] = set_tilemap_cell(false, 0, '0');
	}
	return (RETURN_SUCCESS);
}

int
	init_player(
		t_player *player,
		t_grid *grid)
{
	int	starting_position;

	starting_position = 0;
	if (gridmap_iter(grid, find_starting_position, &starting_position)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (starting_position == 0)
		return (set_error(CUB_NOPLAY));
	gridmap_iter(grid, put_camera, &player->camera);
	return (RETURN_SUCCESS);
}
