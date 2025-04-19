/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/16 17:53:05 by simon         #+#    #+#                 */
/*   Updated: 2025/04/19 20:21:57 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	g_cub_errno = CUB_SUCCESS;

static const char	*cub_strerror(mlx_errno_t val)
{
	const char	*cub_errors[CUB_ERRMAX] = {
		"No Errors.",
		"MLX42 function has failed.",
		"Libft function has failed.",
		"Dynamic memory allocation has failed.",
		"Data file failed to load.",
		"The provided file was invalid / does not exist.",
		"Cub element has invalid type identifier.",
		"Cub colour has invalid format. (R,G,B [0,255])",
		"Cub colour is missing.",
		"Cub texture has invalid format. (png, xpm42)",
		"Cub texture is missing.",
		"Cub map is missing.",
		"Cub map has invalid character. (0,1,N,S,E,W,' ')",
		"Cub map not closed/surrounded by walls.",
		"Cub map has no player position.",
		"Cub map has multiple player positions.",
		"Cub map has invalid door placement."};

	return (cub_errors[val]);
}

int	set_error(const int err_val)
{
	if (err_val)
		g_cub_errno = err_val;
	return (RETURN_ERROR);
}

void	print_error(void)
{
	const int	save_errno = errno;

	errno = 0;
	if (write(STDERR_FILENO, "Error\n", 7) == -1)
		perror(NULL);
	if (g_cub_errno)
		printf("cub_errno: %3d: %s\n", g_cub_errno, cub_strerror(g_cub_errno));
	if (mlx_errno)
		printf("mlx_errno: %3d: %s\n", mlx_errno, mlx_strerror(mlx_errno));
	if (save_errno)
		printf("std_errno: %3d: %s\n", save_errno, strerror(save_errno));
}
