/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:30 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 19:49:04 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_UTILS_H
# define CAMERA_UTILS_H

# include "types.h"

void			center_camera(t_state *state);
void			pan_camera(t_state *state, double delta);
t_screen_coord	world_to_screen(t_world_coord coord, const t_camera *camera);

#endif