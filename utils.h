/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:22:24 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 17:52:37 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

t_state			init_state(void);
void			setup(t_state *state, const char *file_path);
void			free_split(char **str);
int				handle_exit(t_state *state);
void			read_file(t_state *state, const char *file_path);
t_world_coord	new_world_coord(double x, double y, double z);
t_screen_coord	new_screen_coord(int x, int y);
int				ft_atoi_hex(void);
t_line			get_line(t_state *state, t_screen_coord start,
					t_screen_coord end);
int				render(t_state *data);
t_quaternion	track_ball(t_screen_coord delta, t_state *state);

#endif