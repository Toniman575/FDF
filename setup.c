/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:15:16 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 22:58:00 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <sys/time.h>

#include "types.h"
#include "utils.h"

void	init_key_states(t_state *state)
{
	int	i;

	i = 0;
	while (i < COUNT)
	{
		state->key_states[i] = false;
		i++;
	}
	state->cursor_state.pressed = false;
	state->cursor_state.pos.x = 0;
	state->cursor_state.pos.y = 0;
}

void	init_camera(t_state *state)
{
	state->camera.pos = new_world_coord(0., 0., 0.);
	state->camera.rotation.w = 0.880476;
	state->camera.rotation.x = -0.279848;
	state->camera.rotation.y = 0.115917;
	state->camera.rotation.z = -0.364705;
	state->camera.speed = 100.0;
	state->camera.zoom = 1.0;
}

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
	state.world.spacing = 20;
	state.world.height_scale = 5;
	state.world.points = NULL;
	state.world.points_n = 0;
	init_camera(&state);
	state.window_size.x = 500;
	state.window_size.y = 500;
	state.timestamp.tv_sec = 0;
	state.timestamp.tv_usec = 0;
	init_key_states(&state);
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
	if (!state->mlx.image.img)
		handle_exit(state);
	state->mlx.image.addr = mlx_get_data_addr(state->mlx.image.img,
			&state->mlx.image.bits_per_pixel, &state->mlx.image.line_length,
			&state->mlx.image.endian);
	if (gettimeofday(&state->timestamp, NULL) < 0)
		handle_exit(state);
	read_file(state, file_path);
}
