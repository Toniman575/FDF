/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:20 by asadik            #+#    #+#             */
/*   Updated: 2026/03/02 21:27:18 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_utils.h"
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
	zoom_position_correction(&state->camera, old_zoom, new_screen_coord(0, 0));
}

void	reset_rot(t_state *state)
{
	state->camera.rotation = new_quaternion(0.880476, -0.279848, 0.115917,
			-0.364705);
}

void	center_camera(t_state *state)
{
	state->camera.pos = new_world_coord(state->world.size.pixel_w / 2.,
			state->world.size.pixel_h / 2., 0);
}

void	reset_camera(t_state *state)
{
	reset_rot(state);
	reset_zoom(state);
	center_camera(state);
}
