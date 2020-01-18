/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:18 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 15:52:23 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		ft_sort(int *order, double *dist, int num)
{
	int		i;
	int		temp;
	double	temp2;

	i = 0;
	while (i < num - 1)
	{
		if (dist[i] < dist[i + 1])
		{
			temp2 = dist[i + 1];
			dist[i + 1] = dist[i];
			dist[i] = temp2;
			temp = order[i + 1];
			order[i + 1] = order[i];
			order[i] = temp;
			i = 0;
		}
		else
			i++;
	}
}

void		ft_order_sprite(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_sprite)
	{
		env->rc.sp_order[i] = i;
		env->rc.sp_distance[i] = ((env->pos.x - env->tab_sprite[i].pos_x) *
			(env->pos.x - env->tab_sprite[i].pos_x) +
			(env->pos.y - env->tab_sprite[i].pos_y) *
			(env->pos.y - env->tab_sprite[i].pos_y));
		i++;
	}
	ft_sort(env->rc.sp_order, env->rc.sp_distance, env->nb_sprite);
	add_sprite(env);
}

void		ft_place_sprite(t_env *env)
{
	int x;
	int y;
	int i;

	i = 0;
	y = 0;
	while (y < env->map.nb_line)
	{
		x = 0;
		while (x < env->map.nb_char)
		{
			if (env->map.tab_map[y][x] == '2')
			{
				env->tab_sprite[i].pos_x = x + 0.5;
				env->tab_sprite[i].pos_y = y + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
}

int			init_sprite(t_env *env)
{
	int		i;

	i = 0;
	if (!(env->tab_sprite = malloc(sizeof(t_sprite) * env->nb_sprite)))
		return (MALLOC_FAIL);
	if (!(env->rc.sp_order = malloc(sizeof(int) * env->nb_sprite)))
		return (MALLOC_FAIL);
	if (!(env->rc.sp_distance = malloc(sizeof(double) * env->nb_sprite)))
		return (MALLOC_FAIL);
	ft_place_sprite(env);
	ft_order_sprite(env);
	if (env->tab_sprite)
		free(env->tab_sprite);
	if (env->rc.sp_order)
		free(env->rc.sp_order);
	if (env->rc.sp_distance)
		free(env->rc.sp_distance);
	return (SUCCESS);
}
