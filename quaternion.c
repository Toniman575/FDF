/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 19:51:26 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 22:58:00 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "types.h"
#include "utils.h"

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

void	apply_pivot_correction(t_state *state, t_quaternion old_rot)
{
	t_world_coord	screen_center_v;
	t_world_coord	offset1;
	t_world_coord	offset2;

	screen_center_v = new_world_coord((state->window_size.x / 2.0)
			/ state->camera.zoom, (state->window_size.y / 2.0)
			/ state->camera.zoom, 0);
	offset1 = rotate_vector(screen_center_v, old_rot);
	offset2 = rotate_vector(screen_center_v, state->camera.rotation);
	state->camera.pos = new_world_coord(state->camera.pos.x + offset1.x
			- offset2.x, state->camera.pos.y + offset1.y - offset2.y,
			state->camera.pos.z + offset1.z - offset2.z);
}
