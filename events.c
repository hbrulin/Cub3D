/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:24:23 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 20:02:56 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Appuyer sur la touche ESC doit fermer la fenêtre et quitter le programme proprement
//◦ Cliquer sur la croix rouge de la fenêtre doit fermer la fenêtre et quitter le programme proprement

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

int	deal_key(int key, t_env *env)
{
	if (key == KEY_ESCAPE)
	{
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		exit(0);
	}
	// + il faut bien tout free et destroy etc....
	return (key);
}

//pour la croix et force quit
int	deal_exit(t_env *env)
{
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	exit(0);
	// + il faut bien tout free et destroy etc....
}

void	events(t_env *env)
{
	mlx_key_hook (env->win_ptr, deal_key, env);
	mlx_hook(env->win_ptr, 17, StructureNotifyMask, deal_exit, env);
	
	//faire pareil avec mlx hook pour pouvoir rester appuye et que ca avance

	mlx_loop(env->mlx_ptr);
}
