/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:20 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 20:02:55 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_utils.h"
#include "math_utils.h"
#include "types.h"
#include "utils.h"

void	reset_zoom(t_state *state)
{
	double	old_zoom;

	old_zoom = state->camera.zoom.current;
	if (state->world.size.pixel_w > 1 && state->world.size.pixel_h > 1)
	{
		if (state->world.size.pixel_w > state->world.size.pixel_h)
			state->camera.zoom.current = (state->window_size.x * 0.8)
				/ state->world.size.pixel_w;
		else
			state->camera.zoom.current = (state->window_size.y * 0.8)
				/ state->world.size.pixel_h;
	}
	if (state->camera.zoom.current <= 0)
		state->camera.zoom.current = 1.0;
	zoom_position_correction(&state->camera, old_zoom,
		state->window_size.x / 2.0, state->window_size.y / 2.0);
}

void	reset_rot(t_state *state)
{
	t_quaternion	old_rot;

	old_rot = state->camera.rotation;
	state->camera.rotation = new_quaternion(0.880476, -0.279848, 0.115917,
			-0.364705);
	pivot_correction(state, old_rot);
}

void	center_camera(t_state *state)
{
	t_world_coord	center;
	t_world_coord	screen_center;
	t_world_coord	offset;

	center = new_world_coord(state->world.size.pixel_w / 2.,
			state->world.size.pixel_h / 2., 0);
	screen_center = new_world_coord((state->window_size.x / 2.)
			/ state->camera.zoom.current, (state->window_size.y / 2.)
			/ state->camera.zoom.current, 0.);
	offset = rotate_vector(screen_center, state->camera.rotation);
	state->camera.pos = new_world_coord(center.x - offset.x, center.y
			- offset.y, center.z - offset.z);
}

void	reset_camera(t_state *state)
{
	reset_rot(state);
	reset_zoom(state);
	center_camera(state);
}
