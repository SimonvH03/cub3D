/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_weapon.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/19 01:09:37 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	load_texture(
		t_window *window,
		mlx_texture_t **dest,
		const char *directory,
		const char *filename)
{
	char	texture_path[256];

	ft_strlcpy(texture_path, directory, 256);
	ft_strlcat(texture_path, filename, 256);
	ft_strlcat(texture_path, ".xpm42", 256);
	if (access(texture_path, F_OK) != 0)
	{
		*dest = NULL;
		return (RETURN_SUCCESS);
	}
	*dest = modlx_load_xpm42(texture_path);
	if (*dest == NULL)
		return (set_error(CUB_MLXFAIL));
	if (add_to_texture_list(window, *dest) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

static int
	load_animation_textures(
		t_window *window,
		t_list	**frame_list,
		const char *frame_category)
{
	char			filename[256];
	char			frame_id[11];
	unsigned int	i;
	mlx_texture_t	*texture;
	t_list			*new;

	texture = NULL;
	i = 0;
	while (true)
	{
		ft_putnbr_ptr(frame_id, i++);
		ft_strlcpy(filename, frame_category, 256);
		ft_strlcat(filename, frame_id, 256);
		if (load_texture(window, &texture, G1_TEXTURES_PATH, filename)
			!= RETURN_SUCCESS)
			return (RETURN_FAILURE);
		if (texture == NULL)
			return (RETURN_SUCCESS);
		new = ft_lstnew(texture);
		if (new == NULL)
			return (set_error(CUB_MEMFAIL));
		ft_lstadd_front(frame_list, new);
	}
}

static t_scalable *
	store_texture_list_in_array(
		mlx_t *mlx,
		t_list	*texture_list,
		float scale)
{
	t_scalable	*new;
	size_t		size;

	size = ft_lstsize(texture_list);
	new = (t_scalable *)malloc((size + 1) * sizeof(t_scalable));
	if (new == NULL)
	{
		set_error(CUB_MEMFAIL);
		return (NULL);
	}
	new[size].texture = NULL;
	new[size].image = NULL;
	while (size--)
	{
		new[size].texture = texture_list->content;
		new[size].scale = scale;
		if (new_scaled_image(mlx, &new[size]))
			return (NULL);
		texture_list = texture_list->next;
	}
	return (new);
}

static int
	load_weapon_textures(
		t_window *window,
		t_weapon *weapon)
{
	t_list	*textures;
	float	scale;

	textures = NULL;
	if (load_texture(window, &weapon->rest.texture, G1_TEXTURES_PATH, "0")
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	scale = window->mlx->width / (float)weapon->rest.texture->width;
	weapon->rest.scale = scale;
	if (new_scaled_image(window->mlx, &weapon->rest) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (load_animation_textures(window, &textures, "f") != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	weapon->fire = store_texture_list_in_array(window->mlx, textures, scale);
	if (weapon->fire == NULL)
		return (RETURN_FAILURE);
	ft_lstfree(&textures);
	if (load_animation_textures(window, &textures, "r") != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	weapon->reload = store_texture_list_in_array(window->mlx, textures, scale);
	if (weapon->fire == NULL)
		return (RETURN_FAILURE);
	ft_lstfree(&textures);
	return (RETURN_SUCCESS);
}

int
	init_weapon(
		t_window *window,
		t_weapon *weapon)
{
	mlx_t	*mlx;

	mlx = window->mlx;
	ft_bzero(weapon, sizeof(t_weapon));
	weapon->mag_capacity = G1_MAG_CAPACITY;
	weapon->ammo = weapon->mag_capacity;
	weapon->total_ammo = weapon->ammo * G1_SPARE_MAGS;
	weapon->frame_id = -1;
	weapon->frame_time_goal = (1 / (float)G1_FRAME_RATE);
	if (load_weapon_textures(window, weapon) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	weapon->display_img = mlx_new_image(window->mlx,
			mlx->width, weapon->rest.texture->height * weapon->rest.scale);
	if (weapon->display_img == NULL)
		return (set_error(CUB_MLXFAIL));
	if (mlx_image_to_window(mlx, weapon->display_img,
			0, mlx->height - weapon->display_img->height) < 0)
		return (set_error(CUB_MLXFAIL));
	modlx_imgcpy(weapon->display_img, weapon->rest.image);
	return (RETURN_SUCCESS);
}
