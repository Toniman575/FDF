/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:41:08 by asadik            #+#    #+#             */
/*   Updated: 2026/03/18 17:46:19 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_PARSE_UTILS_H
# define READ_PARSE_UTILS_H

# include "types.h"

int				split_n(char **cols);
void			add_world_point(t_state *state, int nums[3],
					int height, int color);
t_world_size	world_pixel_size(t_world *world);
void			normalize_heights(t_world *world);
int				check_hac(char **hac, int *height, int *color);

#endif