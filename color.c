/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 21:02:46 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 21:07:35 by asadik           ###   ########.fr       */
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
