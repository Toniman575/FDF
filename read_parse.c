/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:18:19 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 20:54:41 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "types.h"
#include "libft/libft.h"
#include "utils.h"

int	parse_col(char **row, int row_i, int col_i, t_state *state)
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
		state->world.points[row_i].coord = new_world_coord(
				col_i * state->world.scale,
				row_i * state->world.scale, ft_atoi(hac[0]));
		state->world.points[row_i].color = ft_atoi_hex();
		free_split(hac);
	}
	else
	{
		state->world.points[row_i].coord = new_world_coord(
				(col_i * state->world.scale),
				(row_i * state->world.scale),
				ft_atoi(row[col_i]));
		state->world.points[row_i].color = 0;
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
		if (!parse_col(row, row_i, col_i, state))
		{
			free_split(rows);
			handle_exit(state);
		}
		col_i++;
	}
	free_split(row);
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
	free_split(rows);
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
