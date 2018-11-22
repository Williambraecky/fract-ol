/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:23:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/22 22:49:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		handle_mouseclicks(int button, int x, int y, t_fract *fract)
{
	int count;

	if (fract->ctrl.mouse == 0)
		fract->ctrl.inside_menu = fract->menu->enabled && x < MENU_WIDTH;
	if (button == BUT1_KEY || button == BUT2_KEY || button == BUT3_KEY)
		fract->ctrl.mouse ^= (1L << button);
	if (x < 0 || y < 0)
		return (1);
	count = menu_listener(x, y, fract, 0) ? 1 : 0;
	if (!fract->ctrl.inside_menu && button == SCROLLDOWN_KEY && ++count)
		process_zoom(x, y, fract, 0.05);
	else if (!fract->ctrl.inside_menu && button == SCROLLUP_KEY && ++count)
		process_zoom(x, y, fract, -0.05);
	if (count)
		render(fract);
	return (1);
}

/*
** TODO: Redo movement -> process zoom has accurate movement
*/

int		handle_button_movement(int x, int y, t_fract *fract)
{
	int count;
	int dx;
	int dy;

	if (x < 0 || y < 0)
		return (1);
	dx = fract->ctrl.last_x - x;
	dy = fract->ctrl.last_y - y;
	fract->ctrl.last_x = x;
	fract->ctrl.last_y = y;
	count = menu_listener(x, y, fract, 1) ? 1 : 0;
	if (fract->ctrl.locked == 0 && fract->map->processor == process_julia)
	{
		if (fract->menu->enabled)
			x -= MENU_WIDTH;
		fract->map->real = ft_lerp(-1, 1,
			(double)x / (double)fract->map->image->width);
		fract->map->imaginary = ft_lerp(1, -1,
			(double)y / (double)fract->map->image->height);
		count++;
	}
	if (count)
		render(fract);
	return (1);
}

int		handle_keypress(int key, t_fract *fract)
{
	if (key == ESC_KEY)
		destroy_fract_exit(fract);
	else if (key == MN_KEY && fract->map->max_iter > 7)
		fract->map->max_iter -= 5;
	else if (key == PL_KEY)
		fract->map->max_iter += 5;
	else if (key == M_KEY)
		fract->menu->enabled ^= 1;
	else if (key >= 123 && key <= 126)
		handle_movement(key, fract);
	else if (key == S_KEY)
		fract->map->smooth ^= 1;
	else if (key == K1_KEY)
		fract->map->processor = process_mandelbrot;
	else if (key == K2_KEY)
		fract->map->processor = process_julia;
	else if (key == K3_KEY)
		fract->map->processor = process_burning_ship;
	else if (key == L_KEY)
		fract->ctrl.locked ^= 1;
	else if (key == C_KEY)
		reset_colors(fract);
	else
		return (1);
	if (fract->menu->enabled)
		ft_put_menu(fract);
	render(fract);
	return (1);
}
