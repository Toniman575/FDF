/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:08:29 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 20:25:32 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

#include <math.h>

int	max(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

int	abs(int a)
{
	if (a < 0)
		a = -a;
	return (a);
}

t_screen_coord	round_point(double x, double y)
{
	t_screen_coord	point;

	point.x = round(x);
	point.y = round(y);
	return (point);
}

t_screen_coord	world_to_screen(t_world_coord coord)
{
	t_screen_coord	new;

	new.x = (int)round(coord.x);
	new.y = (int)round(coord.x);
	return (new);
}