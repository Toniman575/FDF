/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 21:24:35 by asadik            #+#    #+#             */
/*   Updated: 2026/03/02 21:27:41 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_utils.h"
#include "types.h"
#include "utils.h"

int	button_down(int button, int x, int y, t_state *state)
{
	if (button == 5 || button == 4)
		zoom_camera(state, button, new_screen_coord(x, y));
	else if (button == 1)
	{
		state->cursor_state.pressed = true;
		state->cursor_state.pos.x = x;
		state->cursor_state.pos.y = y;
	}
	return (1);
}

int	button_up(int button, int x, int y, t_state *state)
{
	(void)x;
	(void)y;
	if (button == 1)
		state->cursor_state.pressed = false;
	return (1);
}

int	cursor_move(int x, int y, t_state *state)
{
	t_screen_coord	delta;

	if (!state->cursor_state.pressed)
	{
		state->cursor_state.pos.x = x;
		state->cursor_state.pos.y = y;
		return (0);
	}
	delta.x = x - state->cursor_state.pos.x;
	delta.y = y - state->cursor_state.pos.y;
	drag_camera(delta, state);
	state->cursor_state.pos.x = x;
	state->cursor_state.pos.y = y;
	return (1);
}
