/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:22:22 by asadik            #+#    #+#             */
/*   Updated: 2026/02/15 18:30:10 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//! TODOS:
//! Before you make the project bigger, make sure you free everything you have right now
//! and handle errors!

#include <mlx.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "libft/libft.h"
#include "fdf.h"

int	ft_atoi_hex(void)
{
	return (0);
}

void	parse_line(char **rows, int row_i, t_world *world)
{
	char	**row;
	int		col_i;
	char	**hac;
	int		index;

	row = ft_split(rows[row_i], ' ');
	col_i = 0;
	while (row[col_i])
	{
		index = row_i * world->width + col_i;
		if (ft_strchr(row[col_i], ','))
		{
			hac = ft_split(row[col_i], ',');
			world->points[index].height = ft_atoi(hac[0]);
			world->points[index].color = ft_atoi_hex();
		}
		else
		{
			world->points[index].height = ft_atoi(row[col_i]);
			world->points[index].color = 0;
		}
		col_i++;
	}
}

void	prepare_world(char **rows, t_world *world)
{
	int		i;

	i = 0;
	world->width = 1;
	while (rows[0][i])
	{
		if (rows[0][i] == ' ')
			world->width++;
		i++;
	}
	i = 0;
	while (rows[i])
		i++;
	world->height = i;
	world->points = ft_calloc(world->width * world->height, sizeof(t_point));
}

void	parse_map(t_world *world, char *map)
{
	char	**rows;
	int		i;

	rows = ft_split(map, '\n');
	prepare_world(rows, world);
	i = 0;
	while (rows[i])
	{
		parse_line(rows, i, world);
		i++;
	}
}

t_world	setup_world(const char *file)
{
	int		fd;
	char	*new_line;
	char	*map;
	t_world	world;

	map = ft_calloc(1, 1);
	fd = open(file, O_RDONLY);
	new_line = get_next_line_single(fd);
	while (new_line)
	{
		map = ft_strjoin(map, new_line);
		new_line = get_next_line_single(fd);
	}
	parse_map(&world, map);
	return (world);
}

t_state	setup(const char *file)
{
	t_state		state;

	state.mlx.mlx_ptr = mlx_init();
	state.mlx.win_ptr = mlx_new_window(state.mlx.mlx_ptr, 500, 500, "FDF");
	state.mlx.image.img = mlx_new_image(state.mlx.mlx_ptr, 500, 500);
	state.mlx.image.addr = mlx_get_data_addr(state.mlx.image.img,
			&state.mlx.image.bits_per_pixel, &state.mlx.image.line_length,
			&state.mlx.image.endian);
	state.mlx.image = state.mlx.image;
	state.world = setup_world(file);
	return (state);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color) {
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	render(t_mlx_data *data)
{
	return (mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0, 0));
}

void	draw_points(t_state *state)
{
	int	i;
	int	size;
	int	scale;
	int	x_start;
	int	y_start;

	i = 0;
	size = 5;
	scale = 20;
	while (i < state->world.height * state->world.width)
	{
		x_start = i % state->world.width * scale;
		y_start = i / state->world.width * scale; 
		for (int y = y_start; y < y_start + size; y++)
		{
			for (int x = x_start; x < x_start + size; x++)
			{
				my_mlx_pixel_put(&state->mlx.image, x, y, 0x00FF0000);
			}
			render(&state->mlx);
		}
		i++;
	}
}

int	main(int varc, char **argv)
{
	t_state		state;

	if (varc != 2)
		return (0);
	state = setup(argv[1]);
	draw_points(&state);
	//render(&state.mlx);
	mlx_loop(state.mlx.mlx_ptr);
}

