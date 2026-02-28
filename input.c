/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 20:25:42 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 20:53:25 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "types.h"
#include "math_utils.h"
#include "utils.h"

t_key	get_key_index(int keycode)
{
	if (keycode == 0xff51)
		return (ARROW_LEFT);
	else if (keycode == 0xff52)
		return (ARROW_UP);
	else if (keycode == 0xff53)
		return (ARROW_RIGHT);
	else if (keycode == 0xff54)
		return (ARROW_DOWN);
	else if (keycode == 0xff1b)
		return (-1);
	else
		return (-2);
}

int	button_down(int button, int x, int y, t_state *state)
{
	double			old_zoom;
	double			factor;
	t_world_coord	m;
	t_world_coord	offset;

	if (button == 5 || button == 4)
	{
		old_zoom = state->camera.zoom;
		if (button == 5)
			state->camera.zoom /= 1.1;
		else
			state->camera.zoom *= 1.1;
		if (state->camera.zoom < 0.1)
			state->camera.zoom = 0.1;
		if (state->camera.zoom > 140.)
			state->camera.zoom = 140.;
		factor = (1.0 / old_zoom) - (1.0 / state->camera.zoom);
		m = new_world_coord((double)x * factor, (double)y * factor, 0);
		offset = rotate_vector(m, state->camera.rotation);
		state->camera.pos.x += offset.x;
		state->camera.pos.y += offset.y;
		state->camera.pos.z += offset.z;
	}
	return (1);
}

int	key_down(int keycode, t_state *state)
{
	int	key;

	key = get_key_index(keycode);
	if (key == -2)
		return (0);
	else if (key == -1)
		mlx_loop_end(state->mlx.mlx_ptr);
	state->key_states[key] = true;
	return (1);
}

int	key_up(int keycode, t_state *state)
{
	int	key;

	key = get_key_index(keycode);
	if (key == -2)
		return (0);
	state->key_states[key] = false;
	return (1);
}
