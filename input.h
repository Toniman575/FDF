/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 20:26:24 by asadik            #+#    #+#             */
/*   Updated: 2026/02/28 21:27:50 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "types.h"

t_key	get_key_index(int keycode);
int		key_down(int keycode, t_state *state);
int		key_up(int keycode, t_state *state);
int		button_down(int button, int x, int y, t_state *state);
int		button_up(int button, int x, int y, t_state *state);
int		cursor_move(int x, int y, t_state *state);

#endif