/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:13:20 by asadik            #+#    #+#             */
/*   Updated: 2026/02/09 13:53:49 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct	s_mlx_data {
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
}				t_mlx_data;

typedef struct	s_point {
	int	height;
	int	color;
}				t_point;

typedef struct	s_world {
	int		width;
	int		height;
	t_point	*points;
}				t_world;

typedef struct	s_state {
	t_image		image;
	t_mlx_data	mlx;
	t_world		world;
}				t_state;

#endif