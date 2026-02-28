/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:18:19 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 20:16:07 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "read_parse_utils.h"
#include "libft/libft.h"
#include "utils.h"

static int	parse_col(char *col, int row_i, int col_i, t_state *state)
{
	char	**hac;
	int		index;

	index = state->world.points_n + col_i;
	if (ft_strchr(col, ','))
	{
		hac = ft_split(col, ',');
		if (!hac)
		{
			free_split(hac);
			return (0);
		}
		state->world.points[index].coord = init_world_coord(col_i, row_i,
				hac[0], state);
		state->world.points[index].color = ft_atoi_hex();
		free_split(hac);
	}
	else
	{
		state->world.points[index].coord = init_world_coord(col_i, row_i,
				col, state);
		state->world.points[index].color = 0;
	}
	return (1);
}

static void	realloc_points(t_state *state, int cols_n, int fd)
{
	t_point	*temp_points;

	temp_points = ft_calloc(state->world.points_n, sizeof(t_point));
	if (!temp_points)
	{
		close(fd);
		handle_exit(state);
	}
	ft_memcpy(temp_points, state->world.points, sizeof(t_point)
		* (state->world.points_n));
	free(state->world.points);
	state->world.points = ft_calloc(state->world.points_n + cols_n,
			sizeof(t_point));
	if (!state->world.points)
	{
		close(fd);
		free(temp_points);
		handle_exit(state);
	}
	ft_memcpy(state->world.points, temp_points, sizeof(t_point)
		* (state->world.points_n));
	free(temp_points);
}

static void	prepare_points(t_state *state, char **cols, int fd)
{
	int		cols_n;

	cols_n = split_n(cols);
	if (!state->world.points)
	{
		state->world.points = ft_calloc(cols_n, sizeof(t_point));
		if (!state->world.points)
		{
			close(fd);
			handle_exit(state);
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
		handle_exit(state);
	}
	prepare_points(state, cols, fd);
	col_i = 0;
	while (cols[col_i])
	{
		if (!parse_col(cols[col_i], row_i, col_i, state))
		{
			free_split(cols);
			close(fd);
			handle_exit(state);
		}
		col_i++;
	}
	state->world.points_n += col_i;
	state->world.width = col_i;
	free_split(cols);
}

void	read_file(t_state *state, const char *file_path)
{
	int		fd;
	int		row_i;
	char	*new_line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		handle_exit(state);
	new_line = get_next_line_single(fd);
	if (!new_line)
	{
		close(fd);
		handle_exit(state);
	}
	row_i = 0;
	while (new_line)
	{
		parse_row(new_line, row_i, state, fd);
		row_i++;
		free(new_line);
		new_line = get_next_line_single(fd);
	}
	state->world.height = row_i;
	free(new_line);
	close(fd);
}
