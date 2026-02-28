/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:20 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 22:58:00 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math_utils.h"
#include "types.h"
#include "utils.h"

void	center_camera(t_state *state)
{
	t_world_coord	center;
	t_world_coord	screen_center;
	t_world_coord	offset;
	double			world_w;
	double			world_h;

	world_w = (state->world.width - 1) * state->world.spacing;
	world_h = (state->world.height - 1) * state->world.spacing;
	if (state->world.width > 1 && state->world.height > 1)
	{
		if (world_w > world_h)
			state->camera.zoom = (state->window_size.x * 0.8) / world_w;
		else
			state->camera.zoom = (state->window_size.y * 0.8) / world_h;
	}
	if (state->camera.zoom <= 0)
		state->camera.zoom = 1.0;
	center = new_world_coord(world_w / 2.0, world_h / 2.0, 0);
	screen_center = new_world_coord((state->window_size.x / 2.0)
			/ state->camera.zoom, (state->window_size.y / 2.0)
			/ state->camera.zoom, 0);
	offset = rotate_vector(screen_center, state->camera.rotation);
	state->camera.pos = new_world_coord(center.x - offset.x, center.y
			- offset.y, center.z - offset.z);
}

void	pan_camera(t_state *state, double delta)
{
	t_world_coord	direction;
	t_world_coord	move;
	double			length;
	double			speed;

	direction = new_world_coord(0, 0, 0);
	if (state->key_states[ARROW_LEFT])
		direction.x -= 1;
	if (state->key_states[ARROW_UP])
		direction.y -= 1;
	if (state->key_states[ARROW_RIGHT])
		direction.x += 1;
	if (state->key_states[ARROW_DOWN])
		direction.y += 1;
	if (direction.x != 0 || direction.y != 0)
	{
		length = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= length;
		direction.y /= length;
		speed = state->camera.speed / state->camera.zoom;
		move = rotate_vector(direction, state->camera.rotation);
		state->camera.pos = new_world_coord(state->camera.pos.x + move.x
				* delta * speed, state->camera.pos.y + move.y * delta * speed,
				state->camera.pos.z + move.z * delta * speed);
	}
}

void	zoom_camera(t_state *state, int button, int x, int y)
{
	double			old_zoom;
	double			factor;
	t_world_coord	mouse_vector;
	t_world_coord	offset;

	old_zoom = state->camera.zoom;
	if (button == 5)
		state->camera.zoom /= 1.1;
	else
		state->camera.zoom *= 1.1;
	if (state->camera.zoom < 0.01)
		state->camera.zoom = 0.01;
	if (state->camera.zoom > 140.)
		state->camera.zoom = 140.;
	factor = (1.0 / old_zoom) - (1.0 / state->camera.zoom);
	mouse_vector = new_world_coord((double)x * factor, (double)y * factor, 0);
	offset = rotate_vector(mouse_vector, state->camera.rotation);
	state->camera.pos = new_world_coord(state->camera.pos.x + offset.x,
			state->camera.pos.y + offset.y, state->camera.pos.z + offset.z);
}

void	rotate_camera(t_state *state, double delta)
{
	t_quaternion	rot;
	double			angle;
	t_quaternion	old_rot;

	angle = 0;
	if (state->key_states[KEY_Q])
		angle -= 2.0 * delta;
	if (state->key_states[KEY_E])
		angle += 2.0 * delta;
	if (angle != 0)
	{
		old_rot = state->camera.rotation;
		rot = quaternion_from_axis_angle(new_world_coord(0, 0, 1), angle);
		state->camera.rotation = quaternion_multiply(state->camera.rotation,
				rot);
		normalize_quaternion(&state->camera.rotation);
		apply_pivot_correction(state, old_rot);
	}
}

void	drag_camera(t_screen_coord	delta, t_state *state)
{
	t_quaternion	old_rot;
	t_quaternion	rot;
	t_quaternion	temp;

	old_rot = state->camera.rotation;
	rot = quaternion_from_axis_angle(new_world_coord(1, 0, 0), delta.y
			* 0.005);
	temp = quaternion_from_axis_angle(new_world_coord(0, 1, 0), -delta.x
			* 0.005);
	rot = quaternion_multiply(rot, temp);
	state->camera.rotation = quaternion_multiply(state->camera.rotation, rot);
	normalize_quaternion(&state->camera.rotation);
	apply_pivot_correction(state, old_rot);
}
