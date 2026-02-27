/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:20 by asadik            #+#    #+#             */
/*   Updated: 2026/02/27 20:24:02 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "types.h"

void	center_camera(t_state *state)
{
	double	world_half_x;
	double	world_half_y;

	world_half_x = (state->world.width - 1) * state->world.spacing / 2;
	world_half_y = (state->world.height - 1) * state->world.spacing / 2;
	state->camera.pos.x = -(state->window_size.width / 2 - world_half_x);
	state->camera.pos.y = -(state->window_size.height / 2 - world_half_x);
}

void	pan_camera(t_state *state, double delta)
{
	t_world_coord	direction;
	double			length;

	direction.x = 0;
	direction.y = 0;
	if (state->key_states[ARROW_LEFT])
		direction.x += 1;
	if (state->key_states[ARROW_UP])
		direction.y += 1;
	if (state->key_states[ARROW_RIGHT])
		direction.x -= 1;
	if (state->key_states[ARROW_DOWN])
		direction.y -= 1;
	if (direction.x != 0 || direction.y != 0)
	{
		length = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= length;
		direction.y /= length;
		state->camera.pos.x += direction.x * delta * state->camera.speed;
		state->camera.pos.y += direction.y * delta * state->camera.speed;
	}
}
