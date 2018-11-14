/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:33:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/14 14:33:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Process each points mapped as x = lerp(-2, 1, ilerp(0, width, pix_x))
** and y = lerp(-1, 1, ilerp(0, height, pix_y)) after applying zoom and movement
** Returns the number of iterations for said pixel
*/

t_pix	ft_process_mandelbrot(float x, float y, int max_iter)
{
	int		iterations;
	float	zx;
	float	zy;
	float	zx2;
	float	zy2;

	iterations = 0;
	zx = 0;
	zy = 0;
	zx2 = zx * zx;
	zy2 = zy * zy;
	while (iterations < max_iter && (zx2 + zy2) < 256)
	{
		zy = 2 * zx * zy + y;
		zx = zx2 - zy2 + x;
		zx2 = zx * zx;
		zy2 = zy * zy;
		iterations++;
	}
	return ((t_pix){.iterations = iterations, .c = (zx2 + zy2)});
}
