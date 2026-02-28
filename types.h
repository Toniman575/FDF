/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:13:20 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 18:23:31 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <sys/time.h>

typedef enum e_key
{
	ARROW_LEFT,
	ARROW_UP,
	ARROW_RIGHT,
	ARROW_DOWN,
	COUNT
}				t_key;

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

typedef struct s_line
{
	t_screen_coord	*points;
	int				length;
}				t_line;

typedef struct s_point
{
	t_world_coord	coord;
	int				color;
}				t_point;

typedef struct s_world
{
	int		width;
	int		height;
	int		spacing;
	t_point	*points;
	int		points_n;
}				t_world;

typedef struct s_camera
{
	t_world_coord	pos;
	double			speed;
}				t_camera;

typedef struct s_window_size
{
	int	width;
	int	height;
}				t_window_size;

typedef struct s_state
{
	t_mlx_data		mlx;
	t_world			world;
	t_camera		camera;
	t_window_size	window_size;
	struct timeval	timestamp;
	bool			key_states[COUNT];
}				t_state;

#endif