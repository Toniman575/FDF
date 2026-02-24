/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:15:16 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 22:39:18 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

#include "types.h"
#include "utils.h"

t_state	init_state(void)
{
	t_state	state;

	state.mlx.image.addr = NULL;
	state.mlx.image.bits_per_pixel = 0;
	state.mlx.image.endian = 0;
	state.mlx.image.img = NULL;
	state.mlx.image.line_length = 0;
	state.mlx.mlx_ptr = NULL;
	state.mlx.win_ptr = NULL;
	state.world.height = 0;
	state.world.width = 0;
	state.world.scale = 20;
	state.world.points = NULL;
	state.world.points_n = 0;
	return (state);
}

void	setup(t_state *state, const char *file_path)
{
	state->mlx.mlx_ptr = mlx_init();
	if (!state->mlx.mlx_ptr)
		handle_exit(state);
	state->mlx.win_ptr = mlx_new_window(state->mlx.mlx_ptr, 500, 500, "FDF");
	if (!state->mlx.win_ptr)
		handle_exit(state);
	state->mlx.image.img = mlx_new_image(state->mlx.mlx_ptr, 500, 500);
	state->mlx.image.addr = mlx_get_data_addr(state->mlx.image.img,
			&state->mlx.image.bits_per_pixel, &state->mlx.image.line_length,
			&state->mlx.image.endian);
	state->mlx.image = state->mlx.image;
	read_file(state, file_path);
}
