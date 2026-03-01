/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:47:02 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 19:07:53 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "types.h"
#include "utils.h"

void	pivot_correction(t_state *state, t_quaternion old_rot)
{
	t_world_coord	screen_center_v;
	t_world_coord	offset1;
	t_world_coord	offset2;

	screen_center_v = new_world_coord((state->window_size.x / 2.0)
			/ state->camera.zoom.current, (state->window_size.y / 2.0)
			/ state->camera.zoom.current, 0);
	offset1 = rotate_vector(screen_center_v, old_rot);
	offset2 = rotate_vector(screen_center_v, state->camera.rotation);
	state->camera.pos = new_world_coord(state->camera.pos.x + offset1.x
			- offset2.x, state->camera.pos.y + offset1.y - offset2.y,
			state->camera.pos.z + offset1.z - offset2.z);
}

void	zoom_position_correction(t_camera *camera, double old_zoom,
		double x, double y)
{
	double			factor;
	t_world_coord	offset_vector;
	t_world_coord	offset;

	factor = (1.0 / old_zoom) - (1.0 / camera->zoom.current);
	offset_vector = new_world_coord(x * factor, y * factor, 0);
	offset = rotate_vector(offset_vector, camera->rotation);
	camera->pos = new_world_coord(camera->pos.x + offset.x,
			camera->pos.y + offset.y, camera->pos.z + offset.z);
}
