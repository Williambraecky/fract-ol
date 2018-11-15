/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:23:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/15 15:26:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_handle_r_press(int x, int y, t_fract *fract)
{
	x -= 301;
	y -= 619;
	if (!fract->menu->enabled || x >= 25 || y >= 255 || x < 0 || y < 0 ||
			!(fract->ctrl.mouse & (1L << BUT1_KEY)) ||
			!fract->ctrl.inside_menu)
		return (0);
	fract->menu->red = y;
	ft_put_rgb_selector(fract->menu);
	ft_put_menu(fract);
	return (0);
}

int		ft_handle_rgb_press(int x, int y, t_fract *fract)
{
	x -= 25;
	y -= 619;
	if (!fract->menu->enabled || x >= 255 || y >= 255 || x < 0 || y < 0 ||
			!fract->ctrl.inside_menu)
		return (0);
	if (fract->ctrl.mouse & (1L << BUT1_KEY))
		fract->menu->start_color = ft_rgb_to_color(fract->menu->red, x, y);
	else if (fract->ctrl.mouse & (1L << BUT2_KEY))
		fract->menu->end_color = ft_rgb_to_color(fract->menu->red, x, y);
	else
		return (0);
	ft_put_rgb_target(fract->menu);
	ft_put_menu(fract);
	return (1);
}

int		handle_mouseclicks(int button, int x, int y, t_fract *fract)
{
	int count;

	if (fract->ctrl.mouse == 0)
		fract->ctrl.inside_menu = fract->menu->enabled && x < MENU_WIDTH;
	if (button == BUT1_KEY || button == BUT2_KEY || button == BUT3_KEY)
		fract->ctrl.mouse ^= (1L << button);
	if (x < 0 || y < 0)
		return (1);
	ft_handle_r_press(x, y, fract);
	count = ft_handle_rgb_press(x, y, fract) ? 1 : 0;
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

	dx = fract->ctrl.last_x - x;
	dy = fract->ctrl.last_y - y;
	fract->ctrl.last_x = x;
	fract->ctrl.last_y = y;
	ft_handle_r_press(x, y, fract);
	count = ft_handle_rgb_press(x, y, fract) ? 1 : 0;
	/*if (!fract->ctrl.inside_menu && fract->ctrl.mouse & (1L << BUT1_KEY))
	{
		count++;
		fract->map->x_offset += 0.003 / fract->map->zoom * (dx / 5);
		fract->map->y_offset += 0.003 / fract->map->zoom * (dy / 5);
	}*/
	if (count)
		render(fract);
	return (1);
}

#include <stdio.h>
void print_debug(t_fract *fract) {
	printf("zoom: %.50f\nx_off: %.50f\ny_off: %.50f\niter: %d\n",
	fract->map->zoom, fract->map->x_offset, fract->map->y_offset, fract->map->max_iter);
}

int		handle_keypress(int key, t_fract *fract)
{
	if (key == D_KEY)
	{
		print_debug(fract);
		return (1);
	}
	if (key == ESC_KEY)
		destroy_fract_exit(fract);
	else if (key == MN_KEY && fract->map->max_iter > 7)
		fract->map->max_iter -= 5;
	else if (key == PL_KEY)
		fract->map->max_iter += 5;
	else if (key == M_KEY)
		fract->menu->enabled ^= 1;
	else if (key == UP_KEY)
		fract->map->y_offset += 0.003 / fract->map->zoom;
	else if (key == DOWN_KEY)
		fract->map->y_offset -= 0.003 / fract->map->zoom;
	else if (key == LEFT_KEY)
		fract->map->x_offset += 0.003 / fract->map->zoom;
	else if (key == RIGHT_KEY)
		fract->map->x_offset -= 0.003 / fract->map->zoom;
	else if (key == S_KEY)
		fract->map->smooth ^= 1;
	else
		return (1);
	if (fract->menu->enabled)
		ft_put_menu(fract);
	render(fract);
	return (1);
}
