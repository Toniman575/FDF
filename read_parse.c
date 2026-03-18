/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:41:07 by anton             #+#    #+#             */
/*   Updated: 2026/03/18 17:53:45 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/error_handling.h"
#include "read_parse_utils.h"
#include "libft/libft.h"
#include "types.h"
#include "utils.h"

static int	parse_col(char *col, int row_i, int col_i, t_state *state)
{
	char		**hac;
	int			nums[3];
	t_result	result;
	int			height;
	int			color;

	nums[0] = state->world.points_n + col_i;
	nums[1] = col_i;
	nums[2] = row_i;
	if (ft_strchr(col, ','))
	{
		hac = ft_split(col, ',');
		if (!check_hac(hac, &height, &color))
			return (free_split(hac), 0);
	}
	else
	{
		result = ft_atoi(col);
		if (result.type == ERROR)
			return (0);
		height = result.value.n;
		color = 0xFFFFFF;
	}
	add_world_point(state, nums, height, color);
	return (1);
}

static void	realloc_points(t_state *state, int cols_n, int fd)
{
	t_world_point	*new_points;
	int				new_size;
	int				old_size_bytes;

	new_size = state->world.points_n + cols_n;
	old_size_bytes = sizeof(t_world_point) * state->world.points_n;
	new_points = ft_calloc(new_size, sizeof(t_world_point));
	if (!new_points)
	{
		clean_parse_exit(state, fd, NULL, NULL);
	}
	if (state->world.points)
		ft_memcpy(new_points, state->world.points, old_size_bytes);
	free(state->world.points);
	state->world.points = new_points;
}

static void	prepare_points(t_state *state, char **cols, int fd, char *row)
{
	int		cols_n;

	cols_n = split_n(cols);
	if (state->world.points_n == 0)
	{
		if (cols_n == 0)
			clean_parse_exit(state, fd, row, cols);
		state->world.size.point_w = cols_n;
	}
	else if (state->world.size.point_w != cols_n)
		clean_parse_exit(state, fd, row, cols);
	if (!state->world.points)
	{
		state->world.points = ft_calloc(cols_n, sizeof(t_world_point));
		if (!state->world.points)
			clean_parse_exit(state, fd, row, cols);
	}
	else
		realloc_points(state, cols_n, fd);
}

void	parse_row(char *row, int row_i, t_state *state, int fd)
{
	int		col_i;
	char	**cols;
	char	*trimmed_row;

	trimmed_row = ft_strtrim(row, " \n");
	if (!trimmed_row)
		clean_parse_exit(state, fd, row, NULL);
	cols = ft_split(trimmed_row, ' ');
	free(trimmed_row);
	if (!cols)
		clean_parse_exit(state, fd, row, NULL);
	prepare_points(state, cols, fd, row);
	col_i = 0;
	while (cols[col_i])
	{
		if (!parse_col(cols[col_i], row_i, col_i, state))
			clean_parse_exit(state, fd, row, cols);
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
	new_line = first_line(fd, state);
	row_i = 0;
	while (new_line)
	{
		parse_row(new_line, row_i, state, fd);
		row_i++;
		free(new_line);
		new_line = get_next_line_single(fd);
	}
	state->world.size.point_h = row_i;
	if (state->world.points_n < 2)
		clean_parse_exit(state, fd, NULL, NULL);
	world_pixel_size(&state->world);
	close(fd);
}
