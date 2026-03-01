/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:20 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 18:53:37 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_utils.h"
#include "math_utils.h"
#include "types.h"
#include "utils.h"

void	reset_zoom(t_state *state)
{
	double	world_w;
	double	world_h;
	double	old_zoom;

	old_zoom = state->camera.zoom.current;
	world_w = (state->world.width - 1) * state->world.spacing;
	world_h = (state->world.height - 1) * state->world.spacing;
	if (state->world.width > 1 && state->world.height > 1)
	{
		if (world_w > world_h)
			state->camera.zoom.current = (state->window_size.x * 0.8) / world_w;
		else
			state->camera.zoom.current = (state->window_size.y * 0.8) / world_h;
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
	state->camera.rotation.w = 0.880476;
	state->camera.rotation.x = -0.279848;
	state->camera.rotation.y = 0.115917;
	state->camera.rotation.z = -0.364705;
	pivot_correction(state, old_rot);
}

void	center_camera(t_state *state)
{
	t_world_coord	center;
	t_world_coord	screen_center;
	t_world_coord	offset;

	center = new_world_coord((state->world.width - 1) * state->world.spacing
			/ 2., (state->world.height - 1) * state->world.spacing / 2., 0);
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
