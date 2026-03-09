/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:07:51 by asadik            #+#    #+#             */
/*   Updated: 2026/03/05 14:37:38 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

#include "types.h"
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

void	draw_line_horizontal(t_state *state, t_screen_point start, t_screen_point end)
{
	t_screen_point	temp;
	t_screen_coord	d;
	int				dir;
	int				p;
	t_screen_coord	current;
	int				i;
	double			t;

	if (start.coord.x > end.coord.x)
	{
		temp = start;
		start = end;
		end = temp;
	}
	d.x = end.coord.x - start.coord.x;
	d.y = end.coord.y - start.coord.y;
	if (d.y < 0)
		dir = -1;
	else
		dir = 1;
	d.y *= dir;
	i = 0;
	current = start.coord;
	p = 2 * d.y - d.x;
	while (i <= d.x)
	{
		current.x = start.coord.x + i;
		if (current.x < state->window_size.x && current.y
			< state->window_size.y && current.x >= 0 && current.y >= 0)
		{
			t = 0.0;
			if (d.x > 0)
				t = (double)i / d.x;
			my_mlx_pixel_put(&state->mlx.image, current,
				lerp_color(start.color, end.color, t));
		}
		if (p >= 0)
		{
			current.y += dir;
			p = p - 2 * d.x;
		}
		p = p + 2 * d.y;
		i++;
	}
}

void	draw_line_vertical(t_state *state, t_screen_point start, t_screen_point end)
{
	t_screen_point	temp;
	t_screen_coord	d;
	int				dir;
	int				p;
	t_screen_coord	current;
	int				i;
	double			t;

	if (start.coord.y > end.coord.y)
	{
		temp = start;
		start = end;
		end = temp;
	}
	d.x = end.coord.x - start.coord.x;
	d.y = end.coord.y - start.coord.y;
	if (d.x < 0)
		dir = -1;
	else
		dir = 1;
	d.x *= dir;
	i = 0;
	current = start.coord;
	p = 2 * d.x - d.y;
	while (i <= d.y)
	{
		current.y = start.coord.y + i;
		if (current.x < state->window_size.x && current.y
			< state->window_size.y && current.x >= 0 && current.y >= 0)
		{
			t = 0.0;
			if (d.y > 0)
				t = (double)i / d.y;
			my_mlx_pixel_put(&state->mlx.image, current,
				lerp_color(start.color, end.color, t));
		}
		if (p >= 0)
		{
			current.x += dir;
			p = p - 2 * d.y;
		}
		p = p + 2 * d.x;
		i++;
	}
}

static void	draw_line(t_state *state, t_screen_point start, t_screen_point end)
{
	if (abs(end.coord.x - start.coord.x) > abs(end.coord.y - start.coord.y))
		draw_line_horizontal(state, start, end);
	else
		draw_line_vertical(state, start, end);
}


static void	draw_lines(t_state *state)
{
	int				i;
	t_screen_point	start;
	t_screen_point	end;

	i = 0;
	while (i < state->world.points_n)
	{
		start = worldp_to_screenp(state->world.points[i], state);
		if ((i + 1) % state->world.size.point_w != 0)
		{
			end = worldp_to_screenp(state->world.points[i + 1], state);
			draw_line(state, start, end);
		}
		if (i + state->world.size.point_w < state->world.points_n)
		{
			end = worldp_to_screenp(state->world.points[i
					+ state->world.size.point_w], state);
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
