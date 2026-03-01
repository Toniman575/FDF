/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:41:08 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 19:48:26 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:22:24 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 22:34:04 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_PARSE_UTILS_H
# define READ_PARSE_UTILS_H

# include "types.h"

int				split_n(char **cols);
t_world_coord	init_world_coord(int col_i, int row_i, char *height,
					t_state *state);
t_world_size	world_pixel_size(t_world *world);

#endif