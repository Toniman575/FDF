/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:38:16 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 18:28:30 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "camera_utils.h"
#include "input.h"
#include "types.h"
#include "utils.h"

static void	register_hooks(t_state *state)
{
	mlx_hook(state->mlx.win_ptr, 2, 1L << 0, &key_down, state);
	mlx_hook(state->mlx.win_ptr, 3, 1L << 1, &key_up, state);
	mlx_hook(state->mlx.win_ptr, 4, 1L << 2, &button_down, state);
	mlx_hook(state->mlx.win_ptr, 5, 1L << 3, &button_up, state);
	mlx_hook(state->mlx.win_ptr, 6, 1L << 6, &cursor_move, state);
	mlx_hook(state->mlx.win_ptr, 17, 0, &mlx_loop_end, state->mlx.mlx_ptr);
	mlx_loop_hook(state->mlx.mlx_ptr, render, state);
}

int	main(int argc, char **argv)
{
	t_state		state;

	if (argc != 2)
		return (0);
	state = init_state();
	setup(&state, argv[1]);
	reset_camera(&state);
	register_hooks(&state);
	mlx_loop(state.mlx.mlx_ptr);
	handle_exit(&state);
}
