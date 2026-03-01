/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:07:51 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 20:03:16 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

#include "math_utils.h"
#include "utils.h"
#include "camera_utils.h"

static void	my_mlx_pixel_put(t_image *image, t_screen_coord coord, int color)
{
	char			*dst;
	unsigned int	address;

	address = (coord.y * image->line_length + coord.x
			* (image->bits_per_pixel / 8));
	dst = image->addr + address;
	*(unsigned int *)dst = color;
}

static void	draw_line(t_state *state, t_screen_coord start, t_screen_coord end)
{
	t_line	line;
	int		i;

	i = 0;
	line = get_line(state, start, end);
	while (i <= line.length)
	{
		if (line.points[i].x < state->window_size.x && line.points[i].y
			< state->window_size.y && line.points[i].x >= 0
			&& line.points[i].y >= 0)
			my_mlx_pixel_put(&state->mlx.image, line.points[i], 0xFFFFFF);
		i++;
	}
	free(line.points);
}

static void	draw_lines(t_state *state)
{
	int				i;
	t_screen_coord	start;
	t_screen_coord	end;

	i = 0;
	while (i < state->world.points_n)
	{
		start = world_to_screen(state->world.points[i].coord, state);
		if ((i + 1) % state->world.size.point_w != 0)
		{
			end = world_to_screen(state->world.points[i
					+ 1].coord, state);
			draw_line(state, start, end);
		}
		if (i + state->world.size.point_w < state->world.points_n)
		{
			end = world_to_screen(state->world.points[i
					+ state->world.size.point_w].coord, state);
			draw_line(state, start, end);
		}
		i++;
	}
}

static void	clear_image(t_state *state)
{
	t_screen_coord	current;

	current = new_screen_coord(0, 0);
	while (current.y < state->window_size.y)
	{
		while (current.x < state->window_size.x)
		{
			my_mlx_pixel_put(&state->mlx.image, current, 0x000000);
			current.x++;
		}
		current.y++;
		current.x = 0;
	}
}

int	render(t_state *state)
{
	struct timeval	ct;
	double			delta;

	clear_image(state);
	if (gettimeofday(&ct, NULL) < 0)
	{
		mlx_loop_end(state->mlx.mlx_ptr);
		return (0);
	}
	delta = ct.tv_sec - state->timestamp.tv_sec
		+ (double)(ct.tv_usec - state->timestamp.tv_usec) / 1000000;
	state->timestamp = ct;
	pan_camera(state, delta);
	rotate_camera(state, delta);
	draw_lines(state);
	mlx_put_image_to_window(state->mlx.mlx_ptr, state->mlx.win_ptr,
		state->mlx.image.img, 0, 0);
	return (1);
}
