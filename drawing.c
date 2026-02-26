/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:07:51 by asadik            #+#    #+#             */
/*   Updated: 2026/02/26 18:31:43 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

#include "math_utils.h"
#include "types.h"
#include "utils.h"

static void	my_mlx_pixel_put(t_image *image, t_screen_coord coord, int color)
{
	char	*dst;

	dst = image->addr + (coord.y * image->line_length + coord.x
			* (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render(t_state *state)
{
	mlx_put_image_to_window(state->mlx.mlx_ptr, state->mlx.win_ptr,
		state->mlx.image.img, 0, 0);
}

static void	put_line(t_image *image, t_line *line)
{
	int	i;

	i = 0;
	while (i <= line->length)
	{
		my_mlx_pixel_put(image, line->points[i], 0xFFFFFF);
		i++;
	}
}

static void	draw_line(t_state *state, t_screen_coord start, t_screen_coord end)
{
	t_line			line;

	line.points = NULL;
	line = get_line(state, start, end);
	put_line(&state->mlx.image, &line);
	free(line.points);
	line.points = NULL;
	line.length = 0;
}

void	draw_lines(t_state *state)
{
	int				i;
	t_screen_coord	start;
	t_screen_coord	end;

	i = 0;
	while (i < state->world.points_n)
	{
		start = world_to_screen(state->world.points[i].coord, &state->camera);
		if ((i + 1) % state->world.width != 0)
		{
			end = world_to_screen(state->world.points[i
					+ 1].coord, &state->camera);
			draw_line(state, start, end);
		}
		if (i / state->world.height < state->world.height - 1)
		{
			end = world_to_screen(state->world.points[i
					+ state->world.width].coord, &state->camera);
			draw_line(state, start, end);
		}
		i++;
	}
}
