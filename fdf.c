/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:22:22 by asadik            #+#    #+#             */
/*   Updated: 2026/02/19 17:41:38 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "libft/libft.h"
#include "fdf.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	handle_exit(t_state *state)
{
	
}

int	ft_atoi_hex(void)
{
	return (0);
}

int	parse_col(char **row, int index, int col_i, t_state *state)
{
	char	**hac;

	if (ft_strchr(row[col_i], ','))
	{
		hac = ft_split(row[col_i], ',');
		if (!hac)
		{
			free_split(row);
			return (0);
		}
		state->world.points[index].height = ft_atoi(hac[0]);
		state->world.points[index].color = ft_atoi_hex();
	}
	else
	{
		state->world.points[index].height = ft_atoi(row[col_i]);
		state->world.points[index].color = 0;
	}
	return (1);
}

void	parse_row(char **rows, int row_i, t_state *state)
{
	char	**row;
	int		col_i;

	row = ft_split(rows[row_i], ' ');
	if (!row)
	{
		free_split(rows);
		handle_exit(state);
	}
	col_i = 0;
	while (row[col_i])
	{
		if (!parse_col(row, row_i * state->world.width + col_i, col_i, state))
		{
			free_split(rows);
			handle_exit(state);
		}
		col_i++;
	}
}

void	prepare_world(char **rows, t_state *state)
{
	int		i;

	i = 0;
	state->world.width = 1;
	while (rows[0][i])
	{
		if (rows[0][i] == ' ')
			state->world.width++;
		i++;
	}
	i = 0;
	while (rows[i])
		i++;
	state->world.height = i;
	state->world.points = ft_calloc(state->world.width * state->world.height,
			sizeof(t_point));
	if (!state->world.points)
	{
		free_split(rows);
		handle_exit(state);
	}
}

void	parse_map(t_state *state, char *map)
{
	char	**rows;
	int		i;

	rows = ft_split(map, '\n');
	if (!rows)
		handle_exit(state);
	prepare_world(rows, state);
	i = 0;
	while (rows[i])
	{
		parse_row(rows, i, state);
		i++;
	}
}

char	*read_file(t_state *state, const char *file_path)
{
	int		fd;
	char	*new_line;
	char	*map;

	map = ft_calloc(1, 1);
	if (!map)
		handle_exit(state);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		handle_exit(state);
	new_line = get_next_line_single(fd);
	if (!new_line)
		handle_exit(state);
	while (new_line)
	{
		map = ft_strjoin(map, new_line);
		if (!map)
		{
			free(new_line);
			handle_exit(state);
		}
		new_line = get_next_line_single(fd);
	}
	close(fd);
	return (map);
}

void	setup_world(t_state *state, const char *file_path)
{
	char	*map;

	map = read_file(state, file_path);
	parse_map(state, map);
}

void	setup(t_state *state, const char *file_path)
{
	state->mlx.mlx_ptr = mlx_init();
	if (!state->mlx.mlx_ptr)
		handle_exit(state);
	state->mlx.win_ptr = mlx_new_window(state->mlx.mlx_ptr, 500, 500, "FDF");
	if (!state->mlx.win_ptr)
		handle_exit(state);
	state->mlx.image.img = mlx_new_image(state->mlx.mlx_ptr, 500, 500);
	state->mlx.image.addr = mlx_get_data_addr(state->mlx.image.img,
			&state->mlx.image.bits_per_pixel, &state->mlx.image.line_length,
			&state->mlx.image.endian);
	state->mlx.image = state->mlx.image;
	setup_world(state, file_path);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render(t_mlx_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->image.img, 0, 0);
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

t_state	init_state(void)
{
	t_state	state;

	state.mlx.image.addr = NULL;
	state.mlx.image.bits_per_pixel = 0;
	state.mlx.image.endian = 0;
	state.mlx.image.img = NULL;
	state.mlx.image.line_length = 0;
	state.mlx.mlx_ptr = NULL;
	state.mlx.win_ptr = NULL;
	state.world.height = 0;
	state.world.width = 0;
	state.world.points = NULL;
	return (state);
}

int	main(int varc, char **argv)
{
	t_state		state;

	if (varc != 2)
		return (0);
	state = init_state();
	setup(&state, argv[1]);
	draw_points(&state);
	//render(&state.mlx);
	mlx_loop(state.mlx.mlx_ptr);
}
