/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:08:29 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 20:08:10 by asadik           ###   ########.fr       */
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
	double			t[3];
	double			w_t[3];

	t[0] = 2.0 * (q.y * v.z - q.z * v.y);
	t[1] = 2.0 * (q.z * v.x - q.x * v.z);
	t[2] = 2.0 * (q.x * v.y - q.y * v.x);
	w_t[0] = q.w * t[0];
	w_t[1] = q.w * t[1];
	w_t[2] = q.w * t[2];
	return (new_world_coord(v.x + w_t[0] + (q.y * t[2] - q.z * t[1]), v.y
			+ w_t[1] + (q.z * t[0] - q.x * t[2]), v.z + w_t[2] + (q.x * t[1]
				- q.y * t[0])));
}

t_screen_coord	world_to_screen(t_world_coord coord, const t_state *state)
{
	t_world_coord	rel;
	t_world_coord	rot;
	t_quaternion	inv_rot;
	double			scale;
	double			dist;

	rel = new_world_coord(coord.x - state->camera.pos.x, coord.y
			- state->camera.pos.y, coord.z - state->camera.pos.z);
	inv_rot = new_quaternion(state->camera.rotation.w,
			-state->camera.rotation.x, -state->camera.rotation.y,
			-state->camera.rotation.z);
	rot = rotate_vector(rel, inv_rot);
	scale = state->camera.zoom.current;
	if (state->camera.projection == PERSPECTIVE)
	{
		dist = max(state->world.size.pixel_w, state->world.size.pixel_h);
		if (dist < 1.0)
			dist = 1000.0;
		if (dist - rot.z < 1.0)
			scale *= dist;
		else
			scale *= dist / (dist - rot.z);
	}
	return (round_point(rot.x * scale, rot.y * scale));
}
