/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:24:23 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/17 16:46:03 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Les touches flèches du gauche et droite du clavier doivent permettre de faire une rotation de la caméra (regarder a gauche et a droite)
// Les touches Z, Q, S et D doivent permettre de déplacer la caméra (déplacement du personnage)

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

int	deal_key(int key, t_env *env)
{

	int x;
	int y;

	//ft_putnbr_fd(key, 1);

	if (key == KEY_ESCAPE)
	{
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		mlx_destroy_image(env->mlx_ptr, env->img->img_ptr);
		exit(0);
	}

	x = env->map.tab_pos[0];
	y = env->map.tab_pos[1];
	if (key == KEY_LEFT)
	{
		if (env->map.player == 'N')
		{
			env->map.player = 'W';
			env->map.tab_map[x][y] = env->map.player;
		}
		if (env->map.player == 'S')
		{
			env->map.player = 'E';
			env->map.tab_map[x][y] = env->map.player;
		}
		if (env->map.player == 'E')
		{
			env->map.player = 'S';
			env->map.tab_map[x][y] = env->map.player;
		}
		if (env->map.player == 'W')
		{
			env->map.player = 'N';
			env->map.tab_map[x][y] = env->map.player;
		}
	}
	if (key == KEY_RIGHT)
	{
		if (env->map.player == 'N')
		{
			env->map.player = 'E';
			env->map.tab_map[x][y] = env->map.player;
		}
		if (env->map.player == 'S')
		{
			env->map.player = 'W';
			env->map.tab_map[x][y] = env->map.player;
		}
		if (env->map.player == 'E')
		{
			env->map.player = 'S';
			env->map.tab_map[x][y] = env->map.player;
		}
		if (env->map.player == 'W')
		{
			env->map.player = 'N';
			env->map.tab_map[x][y] = env->map.player;
		}
	}

	int  i = 0;
	if (key == KEY_SPACEBAR)
	{
		while (env->map.tab_map[i])
		{
			printf("%s\n", env->map.tab_map[i]);
			i++;
		}
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

int	key_move	(int key, t_env *env)
{
	static void (*f_move[4])(t_env *env) = {
		&ft_y_down, &ft_y_up, &ft_x_down, &ft_x_up};

	// j'ai change pour le qwerty
	//est ce que ca va bien avancer en continu?
	if (key == KEY_W)
	{
		if (env->map.player == 'N')
			(*f_move[0])(env);
		if (env->map.player == 'S')
			(*f_move[1])(env);
		if (env->map.player == 'W')
			(*f_move[2])(env);
		if (env->map.player == 'E')
			(*f_move[3])(env);
	}
	if (key == KEY_A)
	{
		if (env->map.player == 'N')
			(*f_move[2])(env);
		if (env->map.player == 'S')
			(*f_move[3])(env);
		if (env->map.player == 'W')
			(*f_move[1])(env);
		if (env->map.player == 'E')
			(*f_move[0])(env);
	}
	if (key == KEY_S)
	{
		if (env->map.player == 'N')
			(*f_move[1])(env);
		if (env->map.player == 'S')
			(*f_move[0])(env);
		if (env->map.player == 'W')
			(*f_move[3])(env);
		if (env->map.player == 'E')
			(*f_move[2])(env);
	}
	if (key == KEY_D)
	{
		if (env->map.player == 'N')
			(*f_move[3])(env);
		if (env->map.player == 'S')
			(*f_move[2])(env);
		if (env->map.player == 'W')
			(*f_move[0])(env);
		if (env->map.player == 'E')
			(*f_move[1])(env);
	}
	return (SUCCESS);
}

void	events(t_env *env)
{
	mlx_key_hook (env->win_ptr, deal_key, env);
	mlx_hook(env->win_ptr, 17, StructureNotifyMask, deal_exit, env);
	mlx_hook(env->win_ptr, KEYPRESS, KEYPRESSMASK, key_move, env);
	
	//faire pareil avec mlx hook pour pouvoir rester appuye et que ca avance

	mlx_loop(env->mlx_ptr);
}
