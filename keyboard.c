/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 20:25:42 by asadik            #+#    #+#             */
/*   Updated: 2026/03/09 22:09:53 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "camera_utils.h"
#include "types.h"

t_key	get_key_index(int keycode)
{
	if (keycode == 0x0061)
		return (KEY_A);
	else if (keycode == 0x0077)
		return (KEY_W);
	else if (keycode == 0x0064)
		return (KEY_D);
	else if (keycode == 0x0073)
		return (KEY_S);
	else if (keycode == 0x0071)
		return (KEY_Q);
	else if (keycode == 0x0065)
		return (KEY_E);
	else if (keycode == 0xFFAB)
		return (KEY_ADD);
	else if (keycode == 0xFFAD)
		return (KEY_SUB);
	else if (keycode == 0xff1b)
		return (-1);
	else
		return (-2);
}

int	key_down(int keycode, t_state *state)
{
	int	index;

	if (keycode == 0x0063)
		return (center_camera(state), 1);
	else if (keycode == 0x0072)
		return (reset_camera(state), 1);
	else if (keycode == 0x0079 || keycode == 0x007a)
		return (reset_rot(state), 1);
	else if (keycode == 0x0078)
		return (reset_zoom(state), 1);
	else if (keycode == 0x0070)
	{
		if (state->camera.projection == PERSPECTIVE)
			state->camera.projection = PARALLEL;
		else
			state->camera.projection = PERSPECTIVE;
		return (1);
	}
	index = get_key_index(keycode);
	if (index == -2)
		return (0);
	else if (index == -1)
		mlx_loop_end(state->mlx.mlx_ptr);
	state->key_states[index] = true;
	return (1);
}

int	key_up(int keycode, t_state *state)
{
	int	index;

	index = get_key_index(keycode);
	if (index == -2)
		return (0);
	state->key_states[index] = false;
	return (1);
}
