/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:07:10 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/07 17:01:33 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

void	ft_rotate(t_env *env, int advance)
{
	double	dir;
	double	plane;

	dir = env->dir.x;
	plane = env->plane.x;
	env->dir.x = env->dir.x * cos(advance * 0.1)
		- env->dir.y * sin(advance * 0.1);
	env->dir.y = dir * sin(advance * 0.1)
		+ env->dir.y * cos(advance * 0.1);
	env->plane.x = env->plane.x * cos(advance * 0.1)
		- env->plane.y * sin(advance * 0.1);
	env->plane.y = plane * sin(advance * 0.1)
		+ env->plane.y * cos(advance * 0.1);
}

void	ft_move(t_env *env)
{
	if (env->up == 1)
	{
		if (!(env->map.tab_map[(int)(env->pos.y)][(int)(env->pos.x + env->dir.x * env->speed)]))
			env->pos.x += env->dir.x * env->speed;
		if (!(env->map.tab_map[(int)(env->pos.y + env->dir.y * env->speed)][(int)(env->pos.x)]))
			env->pos.y += env->dir.y * env->speed;
	}
	if (env->left == 1)
		ft_rotate(env, 1);
	if (env->right == 1)
		ft_rotate(env, -1);
	if (env->down == 1)
	{
		//ORDRE DE CA
		if (!(env->map.tab_map[(int)(env->pos.y)][(int)(env->pos.x - env->dir.x * env->speed)]))
			env->pos.x -= env->dir.x * env->speed;
		if (!(env->map.tab_map[(int)(env->pos.y - env->dir.y * env->speed)][(int)(env->pos.x)]))
			env->pos.y -= env->dir.y * env->speed;
	}
}
