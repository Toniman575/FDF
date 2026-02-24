/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:15:16 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 14:30:12 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "types.h"
#include "libft/libft.h"
#include "utils.h"

void	prepare_world(char **rows, t_state *state)
{
	int		i;

	i = 0;
	state->world.width = 1;
	while (rows[0][i])
	{
		if (rows[0][i] == ' ')
			state->world.width++;
		i++;
	}
	i = 0;
	while (rows[i])
		i++;
	state->world.height = i;
	state->world.points = ft_calloc(state->world.width * state->world.height,
			sizeof(t_point));
	if (!state->world.points)
	{
		free_split(rows);
		handle_exit(state);
	}
}

void	setup_world(t_state *state, const char *file_path)
{
	char	*map;

	map = read_file(state, file_path);
	parse_map(state, map);
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
	setup_world(state, file_path);
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
	state.world.scale = 20;
	state.world.points = NULL;
	return (state);
}
