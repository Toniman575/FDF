/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:13:55 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 20:00:20 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "math_utils.h"
#include "utils.h"

#include <stdlib.h>

static int	diagonal_distance(t_screen_coord start, t_screen_coord end)
{
	int	dx;
	int	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return (max(abs(dx), abs(dy)));
}

static double	lerp(double start, double end, double t)
{
	return (start * ((double)1.0 - t) + t * end);
}

static t_screen_coord	lerp_point(t_screen_coord start, t_screen_coord end, double t)
{
	double	x;
	double	y;

	x = lerp((double)start.x, (double)end.x, t);
	y = lerp((double)start.y, (double)end.y, t);
	return (round_point(x, y));
}

t_line	get_line(t_state *state, t_screen_coord start, t_screen_coord end)
{
	t_line	line;
	int		i;
	double	t;

	i = 0;
	line.length = diagonal_distance(start, end);
	line.points = calloc(line.length, sizeof(t_world_coord));
	if (!line.points)
		handle_exit(state);
	while (i < line.length)
	{
		if (line.length == 0)
			t = 0.0;
		else
			t = (double)i / t;
		line.points[i] = lerp_point(start, end, t);
		i++;
	}
	return (line);
}
