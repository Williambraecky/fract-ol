/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:46:24 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/06 11:33:25 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_fract	*fract;
	fract = ft_new_fract();
	fract->mlx_ptr = mlx_init();
	fract->win_ptr =
	mlx_new_window(fract->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Test");
	ft_init_menu(fract);
	ft_put_menu(fract);
	mlx_key_hook(fract->win_ptr, handle_keypress, fract);
	mlx_loop(fract->mlx_ptr);
	return (0);
}
