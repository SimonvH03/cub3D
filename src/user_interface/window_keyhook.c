#include "../../cub3d.h"

void	window_keyhook(mlx_key_data_t keydata, void *param)
{
	t_window	*window;
	t_camera	*camera;

	window = param;
	camera = &window->scene.camera;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(window->mlx);
	if (window->view == MENU)
	{
		if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
			up_down_select(&window->menu);
		if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
			up_down_select(&window->menu);
		if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
			confirm_selection(&window->menu, window);
	}
	else if (window->view == GAME)
	{
		wasd_move(window, camera);
		arrowkey_turn(window, camera);
		if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
			interact_with_door(&window->scene, camera);
		if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
			toggle_maps(&window->minimap, &window->map);
		if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
			toggle_view(window);
	}
	else if (window->view == MAP)
	{
		wasd_move(window, camera);
		arrowkey_turn(window, camera);
		if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
			toggle_view(window);
	}
} 