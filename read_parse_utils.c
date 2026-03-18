/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:40:09 by asadik            #+#    #+#             */
/*   Updated: 2026/03/18 13:38:06 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	add_world_point(t_state *state, int nums[3], int height, int color)
{
	state->world.points[nums[0]].coord = new_world_coord(nums[1] * state->world
			.spacing, nums[2] * state->world.spacing, height);
	state->world.points[nums[0]].original_z = state->world.points[nums[0]]
		.coord.z;
	state->world.points[nums[0]].color = color;
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
