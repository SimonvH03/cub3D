/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/16 17:53:05 by simon         #+#    #+#                 */
/*   Updated: 2025/04/22 18:26:53 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_cub3d.h"

int	g_cub_errno = CUB_SUCCESS;

static const char	*cub_strerror(mlx_errno_t val)
{
	const char	*cub_errors[CUB_ERRMAX] = {
		"No Errors.",
		"MLX42 function has failed.",
		"Libft function has failed.",
		"Dynamic memory allocation has failed.",
		"The provided file was invalid or does not exist.",
		"Scene element has invalid type identifier.",
		"Scene colour has invalid format. (R,G,B [0,255])",
		"Scene colour is missing.",
		"Scene texture path was invalid or does not exist.",
		"Scene texture has invalid format. (png, xpm42)",
		"Scene texture is missing.",
		"Scene map is missing.",
		"Scene map has invalid character. (0,1,N,S,E,W,' ')",
		"Scene map not closed/surrounded by walls.",
		"Scene map has no player position.",
		"Scene map has multiple player positions."};

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
		perror(NULL);
}
