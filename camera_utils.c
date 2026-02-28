/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:20 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 20:10:42 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math_utils.h"
#include "types.h"

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
	return (round_point(rot.x, rot.y));
}

void	center_camera(t_state *state)
{
	double	world_half_x;
	double	world_half_y;

	world_half_x = ((double)state->world.width - 1.)
		* (double)state->world.spacing / 2.;
	world_half_y = ((double)state->world.height - 1.)
		* (double)state->world.spacing / 2.;
	state->camera.pos.x = -((double)state->window_size.width
			/ 2. - world_half_x);
	state->camera.pos.y = -((double)state->window_size.height
			/ 2. - world_half_y);
}

void	pan_camera(t_state *state, double delta)
{
	t_world_coord	direction;
	t_world_coord	move;
	double			length;

	direction.x = 0;
	direction.y = 0;
	direction.z = 0;
	if (state->key_states[ARROW_LEFT])
		direction.x += 1;
	if (state->key_states[ARROW_UP])
		direction.y -= 1;
	if (state->key_states[ARROW_RIGHT])
		direction.x -= 1;
	if (state->key_states[ARROW_DOWN])
		direction.y += 1;
	if (direction.x != 0 || direction.y != 0)
	{
		length = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= length;
		direction.y /= length;
		move = rotate_vector(direction, state->camera.rotation);
		state->camera.pos.x += move.x * delta * state->camera.speed;
		state->camera.pos.y += move.y * delta * state->camera.speed;
		state->camera.pos.z += move.z * delta * state->camera.speed;
	}
}
