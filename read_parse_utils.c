/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:40:09 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 22:42:02 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

int	get_index(int row_i, int col_i, const t_state *state)
{
	return (row_i * state->world.width + col_i);
}

int	split_n(char **cols)
{
	int		cols_n;

	cols_n = 0;
	while (cols[cols_n])
		cols_n++;
	return (cols_n);
}
