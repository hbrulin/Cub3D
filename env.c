/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:54:20 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/15 13:28:20 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	init_env(t_env *env)
{
	env->width = 800;
	env->height = 600;
	//il faut securiser ici que ces ptr ne renvoient pas NULL
	env->mlx_ptr =  mlx_init();
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->width, env->height, "Cub3D");

	//ou faut-il free les pointeurs/destroy window? en cas d'event
}
