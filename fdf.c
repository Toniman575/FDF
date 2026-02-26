/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:22:22 by asadik            #+#    #+#             */
/*   Updated: 2026/02/26 18:17:39 by asadik           ###   ########.fr       */
/*                                    XK_Left                                        */
/* ************************************************************************** */

#include <mlx.h>
#include <stdbool.h>

#include "camera_utils.h"
#include "types.h"
#include "utils.h"

t_key	get_key_index(int keycode)
{
	if (keycode == 0xff51)
		return ARROW_LEFT;
	else if (keycode == 0xff52)
		return (ARROW_UP);
	else if (keycode == 0xff53)
		return (ARROW_RIGHT);
	else if (keycode == 0xff54)
		return (ARROW_DOWN);
	else
	 	return (-1);
}

int	key_down(int keycode, t_state *state)
{
	t_key	key;

	key = get_key_index(keycode);
	if (key < 0)
		return (0);
	state->key_states[key] = true;
	return (1);
}

int	key_up(int keycode, t_state *state)
{
	t_key	key;

	key = get_key_index(keycode);
	if (key < 0)
		return (0);
	state->key_states[key] = false;
	return (1);
}
void	register_hooks(t_state *state)
{
	mlx_hook(state->mlx.win_ptr, 2, 1L<<0, &key_down, &state);
	mlx_hook(state->mlx.win_ptr, 3, 1L<<1, &key_up, &state);
}

int	main(int varc, char **argv)
{
	t_state		state;

	if (varc != 2)
		return (0);
	state = init_state();
	setup(&state, argv[1]);
	center_camera(&state);
	register_hooks(&state);
	draw_lines(&state);
	render(&state);
	mlx_loop(state.mlx.mlx_ptr);
}
