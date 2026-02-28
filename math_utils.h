/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:15:18 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 17:55:57 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "types.h"

int				max(int a, int b);
int				abs(int a);
t_screen_coord	round_point(double x, double y);
t_screen_coord	world_to_screen(t_world_coord coord, const t_camera *camera);
#endif