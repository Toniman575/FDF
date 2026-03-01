/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 19:57:00 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 20:03:33 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_world_coord	new_world_coord(double x, double y, double z)
{
	t_world_coord	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_screen_coord	new_screen_coord(int x, int y)
{
	t_screen_coord	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_quaternion	new_quaternion(double w, double x, double y, double z)
{
	t_quaternion	new;

	new.w = w;
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
