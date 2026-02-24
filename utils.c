/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:17:52 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 20:38:05 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

#include "types.h"

t_world_coord	new_world_coord(double x, double y, double z)
{
	t_world_coord	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_screen_coord	new_screen_coord(int x, int y)
{
	t_screen_coord	new;

	new.x = x;
	new.y = y;
	return (new);
}

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
	mlx_destroy_image(state->mlx.mlx_ptr, state->mlx.image.img);
	state->mlx.image.addr = NULL;
	mlx_destroy_window(state->mlx.mlx_ptr, state->mlx.win_ptr);
	state->mlx.win_ptr = NULL;
	free(state->world.points);
	state->world.points = NULL;
	free(state->mlx.mlx_ptr);
	state->mlx.mlx_ptr = NULL;
	exit(EXIT_SUCCESS);
}

int	ft_atoi_hex(void)
{
	return (0);
}
