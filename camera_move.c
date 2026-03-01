/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:56:20 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 21:14:48 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_utils.h"
#include "math_utils.h"
#include "types.h"
#include "utils.h"

#include <math.h>

void	pan_camera(t_state *state, double delta)
{
	t_world_coord	direction;
	t_world_coord	move;
	double			length;
	double			speed;

	direction = new_world_coord(0, 0, 0);
	if (state->key_states[KEY_A])
		direction.x -= 1;
	if (state->key_states[KEY_W])
		direction.y -= 1;
	if (state->key_states[KEY_D])
		direction.x += 1;
	if (state->key_states[KEY_S])
		direction.y += 1;
	if (direction.x != 0 || direction.y != 0)
	{
		length = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= length;
		direction.y /= length;
		speed = state->camera.pan_speed / state->camera.zoom.current;
		move = rotate_vector(direction, state->camera.rotation);
		state->camera.pos = new_world_coord(state->camera.pos.x + move.x
				* delta * speed, state->camera.pos.y + move.y * delta * speed,
				state->camera.pos.z + move.z * delta * speed);
	}
}

void	zoom_camera(t_camera *camera, int button, int x, int y)
{
	double			old_zoom;

	old_zoom = camera->zoom.current;
	if (button == 5)
		camera->zoom.current /= camera->zoom.speed;
	else
		camera->zoom.current *= camera->zoom.speed;
	if (camera->zoom.current < camera->zoom.min)
		camera->zoom.current = camera->zoom.min;
	if (camera->zoom.current > camera->zoom.max)
		camera->zoom.current = camera->zoom.max;
	zoom_position_correction(camera, old_zoom, x, y);
}

void	rotate_camera(t_state *state, double delta)
{
	t_quaternion	rot;
	double			angle;
	t_quaternion	old_rot;

	angle = 0;
	if (state->key_states[KEY_Q])
		angle -= 2. * delta;
	if (state->key_states[KEY_E])
		angle += 2. * delta;
	if (angle != 0.)
	{
		old_rot = state->camera.rotation;
		rot = quaternion_from_axis_angle(new_world_coord(0, 0, 1), angle);
		state->camera.rotation = quaternion_multiply(rot,
				state->camera.rotation);
		normalize_quaternion(&state->camera.rotation);
		pivot_correction(state, old_rot);
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
	pivot_correction(state, old_rot);
}
