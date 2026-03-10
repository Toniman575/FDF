/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:40:09 by asadik            #+#    #+#             */
/*   Updated: 2026/03/10 14:18:39 by asadik           ###   ########.fr       */
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
			.spacing, row_i * state->world.spacing, ft_atoi(height)));
}

static void	world_heights(t_world *world)
{
	int	i;

	i = 0;
	while (i < world->points_n)
	{
		if (world->points[i].coord.z > world->max_height)
			world->max_height = world->points[i].coord.z;
		if (world->points[i].coord.z < world->min_height)
			world->min_height = world->points[i].coord.z;
		i++;
	}
}

void	normalize_heights(t_world *world)
{
	int		i;
	double	height_range;

	height_range = (double)world->max_height - (double)world->min_height;
	i = 0;
	while (i < world->points_n)
	{
		if (height_range != 0)
		{
			world->points[i].coord.z = ((world->points[i].original_z
						- world->min_height) / height_range)
				* world->height_scale;
		}
		else
			world->points[i].coord.z = 0;
		i++;
	}
}

void	world_pixel_size(t_world *world)
{
	world->size.pixel_w = (world->size.point_w - 1) * world->spacing;
	world->size.pixel_h = (world->size.point_h - 1) * world->spacing;
	world_heights(world);
	normalize_heights(world);
}
