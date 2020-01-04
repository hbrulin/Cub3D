/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:07:10 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/04 13:38:16 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

void	ft_calc_dir(t_env *env)
{
	env->dir.x = cos(env->pos.angle_d);
	env->dir.y = -(sin(env->pos.angle_d));
}

void	ft_move(t_env *env, int key)
{
//verifier que pas en dehors de la map et pas sur un mur
if (env->pos.x >= 0 && env->pos.x <= ft_strlen(env->map.tab_map[(int)env->pos.y]) && env->pos.y >= 0 && env->pos.y < env->map.nb_line)
{
	if (key == KEY_S)
	{
		env->pos.x -= env->dir.x * 0.1;
		env->pos.y -= env->dir.y * 0.1;
		if (env->map.tab_map[(int)env->pos.y][(int)env->pos.x] == '1')
		{
			env->pos.x += env->dir.x * 0.1;
			env->pos.y += env->dir.y * 0.1;
		}
	}
	else 
	{
		env->pos.x += env->dir.x * 0.1;
		env->pos.y += env->dir.y * 0.1;
		if (env->map.tab_map[(int)env->pos.y][(int)env->pos.x] == '1')
		{
			env->pos.x -= env->dir.x * 0.1;
			env->pos.y -= env->dir.y * 0.1;
		}
	}
}
	
	printf("%f\n", env->pos.x);
	printf("%f\n", env->pos.y);
}
