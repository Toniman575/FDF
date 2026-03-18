/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:18:19 by asadik            #+#    #+#             */
/*   Updated: 2026/03/18 12:13:57 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "read_parse_utils.h"
#include "libft/libft.h"
#include "types.h"
#include "utils.h"

static int	parse_col(char *col, int row_i, int col_i, t_state *state)
{
	char	**hac;
	int		index;

	index = state->world.points_n + col_i;
	if (ft_strchr(col, ','))
	{
		hac = ft_split(col, ',');
		if (!hac || split_n(hac) != 2 || !is_valid_number(hac[0])
			|| !is_valid_hex(hac[1]))
			return (free_split(hac), 0);
		state->world.points[index].coord = init_world_coord(col_i, row_i,
				hac[0], state);
		state->world.points[index].original_z = state->world.points[index]
			.coord.z;
		state->world.points[index].color = ft_atoi_hex(hac[1]);
		free_split(hac);
	}
	else
	{
		if (!is_valid_number(col))
			return (0);
		state->world.points[index].coord = init_world_coord(col_i, row_i,
				col, state);
		state->world.points[index].original_z = state->world.points[index]
			.coord.z;
		state->world.points[index].color = 0xFFFFFF;
	}
	return (1);
}

static void	realloc_points(t_state *state, int cols_n, int fd)
{
	t_world_point	*temp_points;

	temp_points = ft_calloc(state->world.points_n, sizeof(t_world_point));
	if (!temp_points)
	{
		close(fd);
		handle_exit(state, EXIT_FAILURE);
	}
	ft_memcpy(temp_points, state->world.points, sizeof(t_world_point)
		* (state->world.points_n));
	free(state->world.points);
	state->world.points = ft_calloc(state->world.points_n + cols_n,
			sizeof(t_world_point));
	if (!state->world.points)
	{
		close(fd);
		free(temp_points);
		handle_exit(state, EXIT_FAILURE);
	}
	ft_memcpy(state->world.points, temp_points, sizeof(t_world_point)
		* (state->world.points_n));
	free(temp_points);
}

static void	prepare_points(t_state *state, char **cols, int fd)
{
	int		cols_n;

	cols_n = split_n(cols);
	if (state->world.points_n == 0)
	{
		if (cols_n == 0)
		{
			free_split(cols);
			close(fd);
			handle_exit(state, EXIT_FAILURE);
		}
		state->world.size.point_w = cols_n;
	}
	else if (state->world.size.point_w != cols_n)
	{
		free_split(cols);
		close(fd);
		handle_exit(state, EXIT_FAILURE);
	}
	if (!state->world.points)
	{
		state->world.points = ft_calloc(cols_n, sizeof(t_world_point));
		if (!state->world.points)
		{
			close(fd);
			handle_exit(state, EXIT_FAILURE);
		}
	}
	else
		realloc_points(state, cols_n, fd);
}

void	parse_row(char *row, int row_i, t_state *state, int fd)
{
	int		col_i;
	char	**cols;

	cols = ft_split(row, ' ');
	if (!cols)
	{
		free_split(cols);
		close(fd);
		handle_exit(state, EXIT_FAILURE);
	}
	prepare_points(state, cols, fd);
	col_i = 0;
	while (cols[col_i])
	{
		if (!parse_col(cols[col_i], row_i, col_i, state))
		{
			free_split(cols);
			close(fd);
			handle_exit(state, EXIT_FAILURE);
		}
		col_i++;
	}
	state->world.points_n += col_i;
	free_split(cols);
}

void	read_file(t_state *state, const char *file_path)
{
	int		fd;
	int		row_i;
	char	*new_line;
	char	*dot;

	dot = ft_strrchr(file_path, '.');
	if (!dot || ft_strncmp(dot, ".fdf", 5) != 0)
		handle_exit(state, EXIT_FAILURE);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		handle_exit(state, EXIT_FAILURE);
	new_line = get_next_line_single(fd);
	if (!new_line)
	{
		close(fd);
		handle_exit(state, EXIT_FAILURE);
	}
	row_i = 0;
	while (new_line)
	{
		parse_row(new_line, row_i, state, fd);
		row_i++;
		free(new_line);
		new_line = get_next_line_single(fd);
	}
	state->world.size.point_h = row_i;
	free(new_line);
	if (state->world.points_n < 2)
	{
		close(fd);
		handle_exit(state, EXIT_FAILURE);
	}
	world_pixel_size(&state->world);
	close(fd);
}
