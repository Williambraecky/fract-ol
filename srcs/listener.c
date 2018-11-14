/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:23:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/14 14:53:13 by wbraeckm         ###   ########.fr       */
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

	if (x < 0 || y < 0)
		return (1);
	ft_handle_r_press(x, y, fract);
	count = ft_handle_rgb_press(x, y, fract) ? 1 : 0;
	if (fract->ctrl.mouse == 0)
		fract->ctrl.inside_menu = fract->menu->enabled && x < MENU_WIDTH;
	if (button == BUT1_KEY || button == BUT2_KEY || button == BUT3_KEY)
		fract->ctrl.mouse ^= (1L << button);
	if (!fract->ctrl.inside_menu && button == SCROLLDOWN_KEY && ++count)
		fract->map->zoom *= 1.05;
	else if (!fract->ctrl.inside_menu && button == SCROLLUP_KEY && ++count)
		fract->map->zoom *= 0.95;
	if (count)
		render(fract);
	return (1);
}

int		handle_keypress(int key, t_fract *fract)
{
	if (key == ESC_KEY)
		destroy_fract_exit(fract);
	else if (key == MN_KEY && fract->map->max_iter > 5)
		fract->map->max_iter -= 5;
	else if (key == PL_KEY)
		fract->map->max_iter += 5;
	else if (key == M_KEY)
	{
		fract->menu->enabled ^= 1;
		if (fract->menu->enabled)
			ft_put_menu(fract);
	}
	else if (key == UP_KEY)
		fract->map->y_offset -= 5;
	else if (key == DOWN_KEY)
		fract->map->y_offset += 5;
	else if (key == RIGHT_KEY)
		fract->map->x_offset += 5;
	else if (key == LEFT_KEY)
		fract->map->x_offset -= 5;
	else if (key == S_KEY)
		fract->map->smooth ^= 1;
	else
		return (1);
	render(fract);
	return (1);
}
