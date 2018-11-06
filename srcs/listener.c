/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:23:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/06 14:59:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		handle_mouseclicks(int button, int x, int y, t_fract *fract)
{
	int count;

	if (x < 0 || y < 0)
		return (1);
	count = 0;
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
		fract->map->y_offset += 5;
	else if (key == DOWN_KEY)
		fract->map->y_offset -= 5;
	else if (key == RIGHT_KEY)
		fract->map->x_offset -= 5;
	else if (key == LEFT_KEY)
		fract->map->x_offset += 5;
	else
		return (1);
	render(fract);
	return (1);
}
