/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:24:23 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 17:07:27 by hbrulin          ###   ########.fr       */
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

void	events(t_env *env)
{
	mlx_key_hook (env->win_ptr, deal_key, env);


	mlx_loop(env->mlx_ptr);
}
