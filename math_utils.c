/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:08:29 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 17:19:09 by asadik           ###   ########.fr       */
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

t_world_coord	round_point(double x, double y)
{
	t_world_coord	point;

	point.x = round(x);
	point.y = round(y);
	return (point);
}
