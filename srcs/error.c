/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:58:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/06 12:33:21 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	exit_error_destroy(char *message, t_fract *fract)
{
	ft_printf_fd(2, "Error: %s\n", message);
	destroy_fract_exit(fract);
}

void	exit_error(char *message)
{
	ft_printf_fd(2, "Error: %s\n", message);
	exit(0);
}
