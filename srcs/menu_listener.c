/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_listener.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:01:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/22 22:50:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		handle_r_press(int x, int y, t_fract *fract)
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

int		handle_rgb_press(int x, int y, t_fract *fract)
{
	x -= 25;
	y -= 619;
	if (!fract->menu->enabled || x >= 255 || y >= 255 || x < 0 || y < 0 ||
			!fract->ctrl.inside_menu)
		return (0);
	if (fract->menu->current != -1.0 && fract->ctrl.mouse & (1L << BUT1_KEY))
		add_color(fract, ft_rgb_to_color(fract->menu->red, x, y),
			fract->menu->current);
	else if (fract->ctrl.mouse & (1L << BUT1_KEY))
		fract->menu->start_color = ft_rgb_to_color(fract->menu->red, x, y);
	else if (fract->ctrl.mouse & (1L << BUT2_KEY))
		fract->menu->end_color = ft_rgb_to_color(fract->menu->red, x, y);
	else
		return (0);
	ft_put_rgb_target(fract, fract->menu);
	ft_put_menu(fract);
	return (1);
}

int		handle_selector_press(int x, int y, t_fract *fract)
{
	x -= 25;
	y -= 569;
	if (!fract->menu->enabled || x >= 301 || y >= 25 || x < 0 || y < 0 ||
			!fract->ctrl.inside_menu)
		return (0);
	fract->menu->current = (double)x / 300.0;
	return (0);
}

int		menu_listener(int x, int y, t_fract *fract, int is_move)
{
	int	count;

	handle_r_press(x, y, fract);
	count = handle_rgb_press(x, y, fract);
	if (!is_move)
		handle_selector_press(x, y, fract);
	return (count);
}
