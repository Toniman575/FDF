/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:22:24 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 20:38:00 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

t_state			init_state(void);
void			setup(t_state *state, const char *file_path);
void			free_split(char **str);
void			handle_exit(t_state *state);
char			*read_file(t_state *state, const char *file_path);
void			parse_map(t_state *state, char *map);
t_world_coord	new_world_coord(double x, double y, double z);
int				ft_atoi_hex(void);
void			prepare_world(char **rows, t_state *state);
t_line			get_line(t_state *state, t_screen_coord start, t_screen_coord end);
void			draw_lines(t_state *state);
void			render(t_mlx_data *data);

#endif