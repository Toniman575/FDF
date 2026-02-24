/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:13:20 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 17:03:03 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

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

typedef struct s_point
{
	t_world_coord	coord;
	int				color;
}				t_point;

typedef struct s_world
{
	int		width;
	int		height;
	int		scale;
	t_point	*points;
}				t_world;

typedef struct s_state
{
	t_mlx_data	mlx;
	t_world		world;
}				t_state;
#endif