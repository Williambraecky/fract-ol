/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:46:24 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/06 14:46:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char **argv)
{
	t_fract	*fract;

	(void)argc;
	(void)argv;
	if (!(fract = ft_new_fract()))
		exit_error("out of memory");
	if (!(fract->mlx_ptr = mlx_init()))
	{
		free(fract);
		exit_error("could not initialize mlx");
	}
	if (!(fract->win_ptr =
		mlx_new_window(fract->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Test")))
	{
		free(fract);
		exit_error("could not initialize window");
	}
	ft_init_menu(fract);
	mlx_key_hook(fract->win_ptr, handle_keypress, fract);
	mlx_mouse_hook(fract->win_ptr, handle_mouseclicks, fract);
	render(fract);
	mlx_loop(fract->mlx_ptr);
	return (0);
}
