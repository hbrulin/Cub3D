/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:10:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 13:47:29 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int		wrong_char(t_env *env, int i, int j)
{
	if (!(env->map.tab_map[i][j] == '1' || env->map.tab_map[i][j] == '0' ||
		env->map.tab_map[i][j] == '2' || env->map.tab_map[i][j] == 'N' ||
		env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E' ||
		env->map.tab_map[i][j] == 'W'))
		return (WRONG_MAP);
	if (env->map.flag_n == 1 && (env->map.tab_map[i][j] == 'N'
		|| env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E' ||
		env->map.tab_map[i][j] == 'W'))
		return (WRONG_MAP);
	return(SUCCESS);
}

int		closed_map(t_env *env)
{
	int j;

	j = 0;

	while (env->map.tab_map[0][j])
	{
		if (env->map.tab_map[0][j] != '1')
			return (WRONG_MAP);
		j++;
	}
	j = 0;
	while (env->map.tab_map[env->map.nb_line - 1][j])
	{
		if (env->map.tab_map[env->map.nb_line - 1][j] != '1')
			return (WRONG_MAP);
		j++;
	}
	return (SUCCESS);
}

int		ft_parser(t_env *env)
{
	int i;
	int j;
	int k;

	if ((env->error = closed_map(env)) != SUCCESS)
		return (env->error);
	env->map.k_total = ft_strlen(env->map.tab_map[0]) +
		ft_strlen(env->map.tab_map[env->map.nb_line - 1]);
	i = 1;
	j = 1;
	while (env->map.tab_map[i] && i < env->map.nb_line)
	{
		k = ft_strlen(env->map.tab_map[i]);
		env->map.k_total += k;
		j = 1;
		while (env->map.tab_map[i][j])
		{
			if ((env->error = wrong_char(env, i, j)) != SUCCESS)
				return (env->error);
			if (env->map.flag_n == 0 && (env->map.tab_map[i][j] == 'N' || 
				env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E'
				|| env->map.tab_map[i][j] == 'W'))
			{
				env->map.flag_n = 1;
				env->map.player = env->map.tab_map[i][j];
				env->pos.x = j + 0.5; 
				env->pos.y = i + 0.5;
				env->map.tab_map[i][j] = '0';
			}
			if (env->map.tab_map[i][j] == '2')
				env->nb_sprite++;
			j++;
		}
		if (env->map.tab_map[i][0] != '1' || env->map.tab_map[i][k - 1] != '1')
			return (WRONG_MAP);
		i++;
	}
	if ((env->map.k_total % (env->map.nb_line + 1) != 0) || env->map.flag_n == 0)
		return (WRONG_MAP);
	env->map.nb_char = k;
	return (SUCCESS);
}
