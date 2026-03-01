/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:30 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 18:51:13 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_UTILS_H
# define CAMERA_UTILS_H

# include "types.h"

void	center_camera(t_state *state);
void	pan_camera(t_state *state, double delta);
void	rotate_camera(t_state *state, double delta);
void	zoom_camera(t_camera *state, int button, int x, int y);
void	drag_camera(t_screen_coord	delta, t_state *state);
void	reset_camera(t_state *state);
void	reset_rot(t_state *state);
void	reset_zoom(t_state *state);
void	pivot_correction(t_state *state, t_quaternion old_rot);
void	zoom_position_correction(t_camera *camera,
			double old_zoom, double x, double y);

#endif