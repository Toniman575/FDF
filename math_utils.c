/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:08:29 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 17:53:06 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils.h"

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
	return (new_screen_coord(round(x), round(y)));
}

t_world_coord	rotate_vector(t_world_coord v, t_quaternion q)
{
	t_world_coord	res;
	double			t[3];
	double			w_t[3];

	t[0] = 2.0 * (q.y * v.z - q.z * v.y);
	t[1] = 2.0 * (q.z * v.x - q.x * v.z);
	t[2] = 2.0 * (q.x * v.y - q.y * v.x);
	w_t[0] = q.w * t[0];
	w_t[1] = q.w * t[1];
	w_t[2] = q.w * t[2];
	res.x = v.x + w_t[0] + (q.y * t[2] - q.z * t[1]);
	res.y = v.y + w_t[1] + (q.z * t[0] - q.x * t[2]);
	res.z = v.z + w_t[2] + (q.x * t[1] - q.y * t[0]);
	return (res);
}

t_screen_coord	world_to_screen(t_world_coord coord, const t_camera *camera)
{
	t_world_coord	rel;
	t_world_coord	rot;
	t_quaternion	inv_rot;

	rel.x = coord.x - camera->pos.x;
	rel.y = coord.y - camera->pos.y;
	rel.z = coord.z - camera->pos.z;
	inv_rot = camera->rotation;
	inv_rot.x = -inv_rot.x;
	inv_rot.y = -inv_rot.y;
	inv_rot.z = -inv_rot.z;
	rot = rotate_vector(rel, inv_rot);
	return (round_point(rot.x * camera->zoom.current, rot.y
			* camera->zoom.current));
}
