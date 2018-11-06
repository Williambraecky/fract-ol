/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:23:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/06 11:33:30 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		handle_keypress(int key, t_fract *fract)
{
	if (key == ESC_KEY)
		destroy_fract_exit(fract);
	else if (key == M_KEY)
		fract->menu->enabled ^= 1;
	else
		return (1);
	return (1);
}
