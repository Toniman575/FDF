/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:47:02 by asadik            #+#    #+#             */
/*   Updated: 2026/03/02 21:26:24 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "types.h"
#include "utils.h"

void	zoom_position_correction(t_camera *camera, double old_zoom,
		t_screen_coord pos)
{
	double			factor;
	t_world_coord	offset_vector;
	t_world_coord	offset;

	factor = (1.0 / old_zoom) - (1.0 / camera->zoom.current);
	offset_vector = new_world_coord(pos.x * factor, pos.y * factor, 0);
	offset = rotate_vector(offset_vector, camera->rotation);
	camera->pos = new_world_coord(camera->pos.x + offset.x,
			camera->pos.y + offset.y, camera->pos.z + offset.z);
}
