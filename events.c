/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:24:23 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/18 15:42:32 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

void	calc_rad(t_env *env)
{
	if (env->pos.angle_d < 0)
		env->pos.angle_d *= -1;
	env->pos.angle_rad = env->pos.angle_d * M_PI / 180;
}

int	deal_key(int key, t_env *env)
{
	//ft_putnbr_fd(key, 1);

	if (key == KEY_ESCAPE)
	{
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		mlx_destroy_image(env->mlx_ptr, env->img->img_ptr);
		exit(0);
	}

	int  i = 0;
	if (key == KEY_SPACEBAR)
	{
		while (env->map.tab_map[i])
		{
			printf("%s\n", env->map.tab_map[i]);
			i++;
		}
		printf("\n");
		//printf("%\nf", env->pos.angle_rad);
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
	t_pos	*move;

	if (key == KEY_LEFT)
		env->pos.angle_d++;
	if (key == KEY_RIGHT)
	{
		if (env->pos.angle_d == 0) 
			env->pos.angle_d = 360;
		env->pos.angle_d--;
	}
	env->pos.angle_d %= 360;
	printf("%i\n", env->pos.angle_d);
	calc_rad(env); // necessaire?

	if (key == KEY_W || key == KEY_S)
	{
		move = ft_calc(env);
		ft_move(env, move, key);
	}
	if (key == KEY_A)
	{
		env->pos.angle_d += 90;
		env->pos.angle_d %= 360;
		move = ft_calc(env);
		ft_move(env, move, key);
	}
	if (key == KEY_D)
	{
		env->pos.angle_d += 90;
		env->pos.angle_d %= 360;
		move = ft_calc(env);
		ft_move(env, move, key);
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
