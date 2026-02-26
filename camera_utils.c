/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:20 by asadik            #+#    #+#             */
/*   Updated: 2026/02/26 16:18:44 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

void	center_camera(t_state *state)
{
	double	world_half_x;
	double	world_half_y;

	world_half_x = (state->world.width - 1) * state->world.spacing / 2;
	world_half_y = (state->world.height - 1) * state->world.spacing / 2;
	state->camera.pos.x = -(state->window_size.width / 2 - world_half_x);
	state->camera.pos.y = -(state->window_size.height / 2 - world_half_x);
}
