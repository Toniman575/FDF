/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:13:55 by asadik            #+#    #+#             */
/*   Updated: 2026/03/05 14:16:49 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

static double	lerp(double start, double end, double t)
{
	return (start * ((double)1.0 - t) + t * end);
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
