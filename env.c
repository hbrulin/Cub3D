/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:54:20 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 14:21:25 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	ft_init_pos(t_env *env)
{
	if (env->map.player == 'N')
	{
		env->rc.dir.y = -1;
		env->rc.plane.x = -0.80;
	}
	if (env->map.player == 'S')
	{
		env->rc.dir.y = 1;
		env->rc.plane.x = 0.80;
	}
	if (env->map.player == 'E')
	{
		env->rc.dir.x = 1;
		env->rc.plane.y = -0.80;
	}
	if (env->map.player == 'W')
	{
		env->rc.dir.x = -1;
		env->rc.plane.y = 0.80;
	}
	return (SUCCESS);
}

int	init_env_pos(t_env *env)
{
	if (!(env->mlx_ptr = mlx_init()))
		return (MLX_FAIL);
	if ((env->img = ft_new_image(env, env->width, env->height)) == NULL)
		return (IMG_FAIL);
	if ((env->error = ft_init_pos(env)) != SUCCESS)
		return (env->error);
	return (SUCCESS);
}
