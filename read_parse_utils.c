/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:40:09 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 19:52:05 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "types.h"
#include "utils.h"

int	split_n(char **cols)
{
	int		cols_n;

	cols_n = 0;
	while (cols[cols_n])
		cols_n++;
	return (cols_n);
}

t_world_coord	init_world_coord(int col_i, int row_i, char *height,
	t_state *state)
{
	return (new_world_coord(col_i * state->world
			.spacing, row_i * state->world.spacing, ft_atoi(height)
			* state->world.height_scale));
}

void	world_pixel_size(t_world *world)
{
	world->size.pixel_w = (world->size.point_w - 1) * world->spacing;
	world->size.pixel_h = (world->size.point_h - 1) * world->spacing;
}
