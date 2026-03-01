/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:17:52 by asadik            #+#    #+#             */
/*   Updated: 2026/03/01 20:23:38 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

#include "types.h"

void	free_split(char **str)
{
	int	i;

	if (!str)
		return ;
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
	if (state->mlx.image.img)
	{
		mlx_destroy_image(state->mlx.mlx_ptr, state->mlx.image.img);
		state->mlx.image.addr = NULL;
	}
	if (state->mlx.win_ptr)
	{
		mlx_destroy_window(state->mlx.mlx_ptr, state->mlx.win_ptr);
		state->mlx.win_ptr = NULL;
	}
	free(state->world.points);
	state->world.points = NULL;
	free(state->mlx.mlx_ptr);
	state->mlx.mlx_ptr = NULL;
	exit(EXIT_SUCCESS);
}

int	ft_atoi_hex(const char *str)
{
	int	result;
	int	i;
	int	val;

	if (!str)
		return (0);
	result = 0;
	i = 0;
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			val = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			val = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			val = str[i] - 'A' + 10;
		else
			break ;
		result = (result * 16) + val;
		i++;
	}
	return (result);
}
