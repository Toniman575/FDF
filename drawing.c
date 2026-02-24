/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:07:51 by asadik            #+#    #+#             */
/*   Updated: 2026/02/24 17:18:41 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "types.h"

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
