/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocation_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/17 00:13:29 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_to_texture_list(t_window *window, mlx_texture_t *texture_ptr)
{
	t_list	*new;

	new = ft_lstnew(texture_ptr);
	if (new == NULL)
		return (set_error(CUB_MEMFAIL));
	ft_lstadd_front(&window->texture_allocations, new);
	return (RETURN_SUCCESS);
}

void	empty_texture_list(t_window *window)
{
	ft_lstclear(&window->texture_allocations,
		(void (*)(void *))mlx_delete_texture);
}
