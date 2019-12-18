/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:07:10 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/18 15:39:14 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

t_pos	*ft_calc(t_env *env)
{
	t_pos *move;

	if (!(move = malloc(sizeof(t_pos)))) 
		return (NULL); //faire remonter l'erreur
	
	move->x = cos(env->pos.angle_d);
	move->y = -(sin(env->pos.angle_d));

	return (move);
}

void	ft_move(t_env *env, t_pos *move, int key)
{
//verifier que pas en dehors de la map
	if (key == KEY_S)
	{
		env->pos.x -= move->x * 0.1;
		env->pos.y -= move->y * 0.1;
	}
	else
	{
		env->pos.x += move->x * 0.1;
		env->pos.y += move->y * 0.1;	
	}
	
	printf("%f\n", env->pos.x);
	printf("%f\n", env->pos.y);
}
