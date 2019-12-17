/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_move.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:07:10 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/17 16:24:35 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_y_down(t_env *env)
{
	int x;
	int y;

	x = env->map.tab_pos[0];
	y = env->map.tab_pos[1];

	if (env->map.tab_map[x][y - 1] == '0')
	{
		env->map.tab_map[x][y - 1] = env->map.player;
		env->map.tab_map[x][y] = 0;
		env->map.tab_pos[1] = y - 1;
	}
}

void	ft_y_up(t_env *env)
{
	int x;
	int y;

	x = env->map.tab_pos[0];
	y = env->map.tab_pos[1];

	if (env->map.tab_map[x][y + 1] == '0')
	{
		env->map.tab_map[x][y + 1] = env->map.player;
		env->map.tab_map[x][y] = '0';
		env->map.tab_pos[1] = y + 1;
	}
}

void	ft_x_down(t_env *env)
{
	int x;
	int y;

	x = env->map.tab_pos[0];
	y = env->map.tab_pos[1];

	if (env->map.tab_map[x - 1][y] == '0')
	{
		env->map.tab_map[x - 1][y] = env->map.player;
		env->map.tab_map[x][y] = '0';
		env->map.tab_pos[0] = x - 1;
	}
}

void	ft_x_up(t_env *env)
{
	int x;
	int y;

	x = env->map.tab_pos[0];
	y = env->map.tab_pos[1];

	if (env->map.tab_map[x + 1][y] == '0')
	{
		env->map.tab_map[x + 1][y] = env->map.player;
		env->map.tab_map[x][y] = '0';
		env->map.tab_pos[0] = x + 1;
	}
}

