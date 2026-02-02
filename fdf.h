/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:13:20 by asadik            #+#    #+#             */
/*   Updated: 2026/02/02 15:35:32 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct	s_tile {
	int	height;
	int	color;
}				t_tile;

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

typedef struct	s_map {
	int		width;
	int		height;
	t_tile	*tiles;
}				t_map;
#endif