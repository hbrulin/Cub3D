/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:24:23 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/17 15:43:57 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Les touches flèches du gauche et droite du clavier doivent permettre de faire une rotation de la caméra (regarder a gauche et a droite)
// Les touches Z, Q, S et D doivent permettre de déplacer la caméra (déplacement du personnage)

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

int	deal_key(int key, t_env *env)
{
	if (key == KEY_ESCAPE)
	{
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		mlx_destroy_image(env->mlx_ptr, env->img->img_ptr);
		exit(0);
	}

//rotate	
	if (key == KEY_LEFT)
	{
		if (env->map.player == 'N')
			env->map.player = 'W';
		if (env->map.player == 'S')
			env->map.player = 'E';
		if (env->map.player == 'E')
			env->map.player = 'S';
		if (env->map.player == 'W')
			env->map.player = 'N';
	}
	if (key == KEY_RIGHT)
	{
		if (env->map.player == 'N')
			env->map.player = 'E';
		if (env->map.player == 'S')
			env->map.player = 'W';
		if (env->map.player == 'E')
			env->map.player = 'S';
		if (env->map.player == 'W')
			env->map.player = 'N';
	}
	return (key);
}

//pour la croix et force quit
int	deal_exit(t_env *env)
{
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	mlx_destroy_image(env->mlx_ptr, env->img->img_ptr);
	exit(0);
	// + il faut bien tout free et destroy etc....
}

int	move	(int key, t_env *env)
{
	// j'ai change pour le qwery
	if (key == KEY_W)
	if (key == KEY_A)
	if (key == KEY_S)
	if (key == KEY_D)

}

void	events(t_env *env)
{
	mlx_key_hook (env->win_ptr, deal_key, env);
	mlx_hook(env->win_ptr, 17, StructureNotifyMask, deal_exit, env);
	mlx_hook(env->win_ptr, KEYPRESS, KEYPRESSMASK, move, env);
	
	//faire pareil avec mlx hook pour pouvoir rester appuye et que ca avance

	mlx_loop(env->mlx_ptr);
}
