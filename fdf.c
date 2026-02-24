/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:22:22 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 20:31:08 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "types.h"
#include "utils.h"

int	main(int varc, char **argv)
{
	t_state		state;

	if (varc != 2)
		return (0);
	state = init_state();
	setup(&state, argv[1]);
	draw_lines(&state);
	render(&state.mlx);
	mlx_loop(state.mlx.mlx_ptr);
}
