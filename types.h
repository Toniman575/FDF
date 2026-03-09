/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:13:20 by asadik            #+#    #+#             */
/*   Updated: 2026/03/09 11:54:30 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <sys/time.h>

typedef enum e_key
{
	KEY_A,
	KEY_W,
	KEY_D,
	KEY_S,
	KEY_Q,
	KEY_E,
	COUNT
}				t_key;

typedef enum e_projection
{
	PARALLEL,
	PERSPECTIVE
}				t_projection;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	image;
}				t_mlx_data;

typedef struct s_world_coord
{
	double	x;
	double	y;
	double	z;
}				t_world_coord;

typedef struct s_screen_coord
{
	int	x;
	int	y;
}				t_screen_coord;

typedef struct s_world_point
{
	t_world_coord	coord;
	int				color;
}				t_world_point;

typedef struct s_screen_point
{
	t_screen_coord	coord;
	int				color;
}				t_screen_point;

typedef struct s_world_size
{
	int	point_w;
	int	point_h;
	int	pixel_w;
	int	pixel_h;
}				t_world_size;

typedef struct s_world
{
	t_world_size	size;
	int				spacing;
	int				height_scale;
	t_world_point	*points;
	int				points_n;
}				t_world;

typedef struct s_quaternion
{
	double	w;
	double	x;
	double	y;
	double	z;
}				t_quaternion;

typedef struct s_zoom
{
	double	current;
	double	speed;
	double	min;
	double	max;
}				t_zoom;

typedef struct s_camera
{
	t_world_coord	pos;
	t_quaternion	rotation;
	t_zoom			zoom;
	double			pan_speed;
	double			rot_speed;
	t_projection	projection;
}				t_camera;

typedef struct s_cursor
{
	t_screen_coord	pos;
	bool			pressed;
}				t_cursor;

typedef struct s_bresenham
{
	t_screen_coord	step;
	int				dir;
	int				p;
}				t_bresenham;

typedef struct s_state
{
	t_mlx_data		mlx;
	t_world			world;
	t_camera		camera;
	t_screen_coord	window_size;
	struct timeval	timestamp;
	bool			key_states[COUNT];
	t_cursor		cursor_state;
}				t_state;

#endif