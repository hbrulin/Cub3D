/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:24:23 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 17:15:26 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Appuyer sur la touche ESC doit fermer la fenêtre et quitter le programme proprement
//◦ Cliquer sur la croix rouge de la fenêtre doit fermer la fenêtre et quitter le programme proprement

#include "cub3d.h"
#include <stdio.h>

int	deal_key(int key, t_env *env)
{
	//ft_putnbr_fd(key, 1);
	if (key == 53)
	{
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		exit(0);
	}
	return (key);
}

/*int	deal_mouse(int button, int x, int y, t_env *env)
{
	ft_putnbr_fd(button, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(x, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(y, 1);

	if (button == 1)
	{
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		exit(0);
	}

	return (button);
}*/


void	events(t_env *env)
{
	mlx_key_hook (env->win_ptr, deal_key, env);

	//comment faire pour exit lorsque clic sur la croix??
	//mlx_mouse_hook (env->win_ptr, deal_mouse, env);

	mlx_loop(env->mlx_ptr);
}
