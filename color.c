/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 21:02:46 by asadik            #+#    #+#             */
/*   Updated: 2026/03/09 12:17:37 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "types.h"

t_screen_point	worldp_to_screenp(t_world_point point, t_state *state)
{
	t_screen_point	new;

	new.coord = world_to_screen(point.coord, state);
	new.color = point.color;
	return (new);
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

int	get_color(double f, int i, int start_color, int end_color)
{
	double			t;

	t = 0.0;
	if (f > 0)
		t = (double)i / f;
	return (lerp_color(start_color, end_color, t));
}
