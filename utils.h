/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:22:24 by asadik            #+#    #+#             */
/*   Updated: 2026/03/18 11:43:09 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

t_state			init_state(void);
void			setup(t_state *state, const char *file_path);
void			free_split(char **str);
int				handle_exit(t_state *state, int status);
void			read_file(t_state *state, const char *file_path);
t_world_coord	new_world_coord(double x, double y, double z);
t_screen_coord	new_screen_coord(int x, int y);
t_quaternion	new_quaternion(double w, double x, double y, double z);
int				ft_atoi_hex(const char *str);
int				render(t_state *data);
int				lerp_color(int start, int end, double t);
t_quaternion	track_ball(t_screen_coord delta, t_state *state);
t_screen_point	worldp_to_screenp(t_world_point point, t_state *state);
int				get_color(double f, int i, int start_color, int end_color);
void			my_mlx_pixel_put(t_image *image, t_screen_coord coord,
					int color);
void			draw_line_vertical(t_state *state, t_screen_point start,
					t_screen_point end);
void			draw_line_horizontal(t_state *state, t_screen_point start,
					t_screen_point end);
int				ft_ishex(char c);
int				is_valid_hex(const char *str);
int				is_valid_number(const char *str);

#endif