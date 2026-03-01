/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:15:18 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 19:32:05 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "types.h"

int				max(int a, int b);
int				abs(int a);
t_screen_coord	round_point(double x, double y);
t_world_coord	rotate_vector(t_world_coord v, t_quaternion q);
t_quaternion	quaternion_multiply(t_quaternion q1, t_quaternion q2);
void			normalize_quaternion(t_quaternion *q);
t_quaternion	quaternion_from_axis_angle(t_world_coord axis, double angle);
t_screen_coord	world_to_screen(t_world_coord coord, const t_state *state);

#endif