/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:15:18 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 17:20:42 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "types.h"

int				max(int a, int b);
int				abs(int a);
t_world_coord	round_point(double x, double y);
#endif