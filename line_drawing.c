/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:13:55 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 17:19:29 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "math_utils.h"

int	diagonal_distance(const t_world_coord *start, const t_world_coord *end)
{
	int	dx;
	int	dy;

	dx = end->x - start->x;
	dy = end->y - start->y;
	return (max(abs(dx), abs(dy)));
}

static double	lerp(double start, double end, double t)
{
	return (start * ((double)1.0 - t) + t * end);
}

static t_world_coord	lerp_point(const t_world_coord *start,
	const t_world_coord *end, double t)
{
	double	x;
	double	y;

	x = lerp((double)start->x, (double)start->x, t);
	y = lerp((double)start->y, (double)start->y, t);
	return (round_point(x, y));
}
