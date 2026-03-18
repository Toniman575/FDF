/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:39:08 by anton             #+#    #+#             */
/*   Updated: 2026/03/18 17:59:44 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "read_parse_utils.h"
#include "types.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_ishex(char c)
{
	return (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

int	is_valid_hex(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	else
		return (0);
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_ishex(str[i++]))
			return (0);
	}
	return (1);
}

void	clean_parse_exit(t_state *state, int fd, char *row, char **cols)
{
	if (row)
		free(row);
	if (cols)
		free_split(cols);
	if (fd >= 0)
		close(fd);
	handle_exit(state, EXIT_FAILURE);
}

int	check_hac(char **hac, int *height, int *color)
{
	t_result	result;

	if (!hac || split_n(hac) != 2 || !is_valid_hex(hac[1]))
		return (free_split(hac), 0);
	result = ft_atoi(hac[0]);
	if (result.type == ERROR)
		return (free_split(hac), 0);
	*height = result.value.n;
	*color = ft_atoi_hex(hac[1]);
	free_split(hac);
	return (1);
}

char	*first_line(int fd, t_state *state)
{
	char	*new_line;

	if (fd < 0)
		handle_exit(state, EXIT_FAILURE);
	new_line = get_next_line_single(fd);
	if (!new_line)
		clean_parse_exit(state, fd, NULL, NULL);
	return (new_line);
}
