/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:38:16 by asadik            #+#    #+#             */
/*   Updated: 2026/02/27 20:39:37 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdbool.h>

#include "camera_utils.h"
#include "input.h"
#include "types.h"
#include "utils.h"

static void	register_hooks(t_state *state)
{
	mlx_hook(state->mlx.win_ptr, 2, 1L << 0, &key_down, state);
	mlx_hook(state->mlx.win_ptr, 3, 1L << 1, &key_up, state);
	mlx_hook(state->mlx.win_ptr, 17, 0, &mlx_loop_end, state->mlx.mlx_ptr);
	mlx_loop_hook(state->mlx.mlx_ptr, render, state);
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
	mlx_loop(state.mlx.mlx_ptr);
	handle_exit(&state);
}
