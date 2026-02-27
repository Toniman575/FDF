/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 20:25:42 by asadik            #+#    #+#             */
/*   Updated: 2026/02/27 20:27:21 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdbool.h>

#include "types.h"

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
	if (key < 0)
		return (0);
	state->key_states[key] = false;
	return (1);
}
