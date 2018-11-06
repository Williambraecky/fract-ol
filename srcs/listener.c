/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:23:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/06 12:54:57 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		handle_keypress(int key, t_fract *fract)
{
	if (key == ESC_KEY)
		destroy_fract_exit(fract);
	else if (key == MN_KEY && fract->map->max_iter > 5)
	{
		fract->map->max_iter -= 5;
		render(fract);
	}
	else if (key == PL_KEY)
	{
		fract->map->max_iter += 5;
		render(fract);
	}
	else if (key == M_KEY)
	{
		ft_printf("m key pressed\n");
		fract->menu->enabled ^= 1;
		if (fract->menu->enabled)
			ft_put_menu(fract);
		render(fract);
	}
	else
		return (1);
	return (1);
}
