/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:07:10 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/18 19:48:00 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

void	ft_move(t_env *env, int key)
{
//verifier que pas en dehors de la map et pas sur un mur
	if (key == KEY_S)
	{
		env->pos.x -= env->dir.x * 0.1;
		env->pos.y -= env->dir.y * 0.1;
	}
	else
	{
		env->pos.x += env->dir.x * 0.1;
		env->pos.y += env->dir.y * 0.1;	
	}
	
	printf("%f\n", env->pos.x);
	printf("%f\n", env->pos.y);
}
