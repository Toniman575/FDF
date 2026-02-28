/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:20 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 20:59:55 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math_utils.h"
#include "types.h"
#include "utils.h"

t_screen_coord	world_to_screen(t_world_coord coord, const t_camera *camera)
{
	t_world_coord	rel;
	t_world_coord	rot;
	t_quaternion	inv_rot;

	rel.x = coord.x - camera->pos.x;
	rel.y = coord.y - camera->pos.y;
	rel.z = coord.z - camera->pos.z;
	inv_rot = camera->rotation;
	inv_rot.x = -inv_rot.x;
	inv_rot.y = -inv_rot.y;
	inv_rot.z = -inv_rot.z;
	rot = rotate_vector(rel, inv_rot);
	return (round_point(rot.x * camera->zoom, rot.y * camera->zoom));
}

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
			state->camera.zoom = (state->window_size.width * 0.8) / world_w;
		else
			state->camera.zoom = (state->window_size.height * 0.8) / world_h;
	}
	if (state->camera.zoom <= 0)
		state->camera.zoom = 1.0;
	center = new_world_coord(world_w / 2.0, world_h / 2.0, 0);
	screen_center = new_world_coord((state->window_size.width / 2.0)
			/ state->camera.zoom, (state->window_size.height / 2.0)
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
