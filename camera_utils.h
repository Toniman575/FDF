/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:45:30 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 17:37:48 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_UTILS_H
# define CAMERA_UTILS_H

# include "types.h"

void	center_camera(t_state *state);
void	pan_camera(t_state *state, double delta);
void	rotate_camera(t_state *state, double delta);
void	zoom_camera(t_state *state, int button, int x, int y);
void	drag_camera(t_screen_coord	delta, t_state *state);

#endif