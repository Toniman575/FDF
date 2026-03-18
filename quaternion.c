/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 19:51:26 by asadik            #+#    #+#             */
/*   Updated: 2026/03/18 17:16:33 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "types.h"

#include <math.h>

t_quaternion	quaternion_multiply(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	res;

	res.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	res.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	res.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	res.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (res);
}

void	normalize_quaternion(t_quaternion *q)
{
	double	len;

	len = sqrt(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
	if (len == 0)
		return ;
	q->w /= len;
	q->x /= len;
	q->y /= len;
	q->z /= len;
}

t_quaternion	quaternion_from_axis_angle(t_world_coord axis, double angle)
{
	t_quaternion	q;
	double			half_angle;
	double			s;

	half_angle = angle * 0.5;
	s = sin(half_angle);
	q.w = cos(half_angle);
	q.x = axis.x * s;
	q.y = axis.y * s;
	q.z = axis.z * s;
	return (q);
}
