/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:13:55 by asadik            #+#    #+#             */
/*   Updated: 2026/03/09 12:27:44 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils.h"
#include <mlx.h>

double	lerp(double start, double end, double t)
{
	return (start * ((double)1.0 - t) + t * end);
}

t_bresenham	init_bresenham_h(t_screen_point *start, t_screen_point *end)
{
	t_screen_point	temp;
	t_bresenham		util;

	if (start->coord.x > end->coord.x)
	{
		temp = *start;
		*start = *end;
		*end = temp;
	}
	util.step.x = end->coord.x - start->coord.x;
	util.step.y = end->coord.y - start->coord.y;
	if (util.step.y < 0)
		util.dir = -1;
	else
		util.dir = 1;
	util.step.y *= util.dir;
	util.p = 2 * util.step.y - util.step.x;
	return (util);
}

void	draw_line_horizontal(t_state *state, t_screen_point start,
		t_screen_point end)
{
	t_bresenham		util;
	t_screen_coord	current;
	int				i;

	util = init_bresenham_h(&start, &end);
	i = 0;
	current = start.coord;
	while (i <= util.step.x)
	{
		current.x = start.coord.x + i;
		if (current.x < state->window_size.x && current.y
			< state->window_size.y && current.x >= 0 && current.y >= 0)
			my_mlx_pixel_put(&state->mlx.image, current,
				get_color(util.step.x, i, start.color, end.color));
		if (util.p >= 0)
		{
			current.y += util.dir;
			util.p = util.p - 2 * util.step.x;
		}
		util.p = util.p + 2 * util.step.y;
		i++;
	}
}

t_bresenham	init_bresenham_v(t_screen_point *start, t_screen_point *end)
{
	t_screen_point	temp;
	t_bresenham		util;

	if (start->coord.y > end->coord.y)
	{
		temp = *start;
		*start = *end;
		*end = temp;
	}
	util.step.x = end->coord.x - start->coord.x;
	util.step.y = end->coord.y - start->coord.y;
	if (util.step.x < 0)
		util.dir = -1;
	else
		util.dir = 1;
	util.step.x *= util.dir;
	util.p = 2 * util.step.x - util.step.y;
	return (util);
}

void	draw_line_vertical(t_state *state, t_screen_point start,
		t_screen_point end)
{
	t_bresenham		util;
	t_screen_coord	current;
	int				i;

	util = init_bresenham_v(&start, &end);
	i = 0;
	current = start.coord;
	while (i <= util.step.y)
	{
		current.y = start.coord.y + i;
		if (current.x < state->window_size.x && current.y
			< state->window_size.y && current.x >= 0 && current.y >= 0)
			my_mlx_pixel_put(&state->mlx.image, current,
				get_color(util.step.y, i, start.color, end.color));
		if (util.p >= 0)
		{
			current.x += util.dir;
			util.p = util.p - 2 * util.step.y;
		}
		util.p = util.p + 2 * util.step.x;
		i++;
	}
}
