/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:13:55 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 20:53:03 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "math_utils.h"

#include <mlx.h>

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

static t_screen_coord	lerp_point(t_screen_coord start, t_screen_coord end,
	double t)
{
	double	x;
	double	y;

	x = lerp((double)start.x, (double)end.x, t);
	y = lerp((double)start.y, (double)end.y, t);
	return (round_point(x, y));
}

int	lerp_color(int start, int end, double t)
{
	int	r;
	int	g;
	int	b;

	r = lerp((start >> 16) & 0xFF, (end >> 16) & 0xFF, t);
	g = lerp((start >> 8) & 0xFF, (end >> 8) & 0xFF, t);
	b = lerp(start & 0xFF, end & 0xFF, t);
	return ((r << 16) | (g << 8) | b);
}

t_line	get_line(t_state *state, t_screen_coord start, t_screen_coord end)
{
	t_line	line;
	int		i;
	double	t;

	i = 0;
	line.length = diagonal_distance(start, end);
	line.points = ft_calloc(line.length + 1, sizeof(t_screen_coord));
	if (!line.points)
		mlx_loop_end(state->mlx.mlx_ptr);
	while (i <= line.length)
	{
		if (line.length == 0 || i == 0)
			t = 0.0;
		else
			t = (double)i / line.length;
		line.points[i] = lerp_point(start, end, t);
		i++;
	}
	return (line);
}
