/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:54:20 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 11:47:07 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	ft_init(t_env *env)
{
	if (env->map.player == 'N')
	{
		env->rc.dir.x = 0;
		env->rc.dir.y = -1;
		env->rc.plane.x = -0.80;
		env->rc.plane.y = 0;
	}
	if (env->map.player == 'S')
	{
		env->rc.dir.x = 0;
		env->rc.dir.y = 1;
		env->rc.plane.x = 0.80;
		env->rc.plane.y = 0;
	}
	if (env->map.player == 'E')
	{
		env->rc.dir.x = 1;
		env->rc.dir.y = 0;
		env->rc.plane.x = 0;
		env->rc.plane.y = -0.80;
	}
	if (env->map.player == 'W')
	{
		env->rc.dir.x = -1;
		env->rc.dir.y = 0;
		env->rc.plane.x = 0;
		env->rc.plane.y = 0.80;
	}

	if (!(env->rc.zbuffer = malloc(sizeof(double) * env->width)))
		return (MALLOC_FAIL);

	if((env->tex1 = ft_new_tex(env, env->data.NO)) == NULL)
		return (WRONG_TEX);
	if((env->tex2 = ft_new_tex(env, env->data.SO)) == NULL)
		return (WRONG_TEX);
	if((env->tex3 = ft_new_tex(env, env->data.EA)) == NULL)
		return (WRONG_TEX);
	if((env->tex4 = ft_new_tex(env, env->data.WE)) == NULL)
		return (WRONG_TEX);
	if((env->sprite = ft_new_tex(env, env->data.SP)) == NULL)
		return (WRONG_TEX);
	return (SUCCESS);
}


int	init_env(t_env *env)
{
	int i;
	char **tab;
	int error;

	if ((error = get_color(&env->color_floor, env->data.F)) != SUCCESS)
		return(error);
	if ((error = get_color(&env->color_ceiling, env->data.C)) != SUCCESS)
		return(error);

	i = 0;
	while (!ft_isdigit(env->data.R[i]))
		i++;
	if(!(tab = ft_split(env->data.R + i, ' ')))
		return (MALLOC_FAIL);
	if (tab[0])
		env->width = ft_atoi(tab[0]);
	if (tab[1])
		env->height = ft_atoi(tab[1]);
	ft_tabdel((void **)tab); 
	if (!env->width || !env->height || env->width < 0 || env->height < 0)
		return (WRONG_INPUT);
	if (env->width > MAX_WIDTH)
		env->width = MAX_WIDTH;
	if (env->height > MAX_HEIGHT)
		env->height = MAX_HEIGHT;
	if(!(env->mlx_ptr =  mlx_init()))
		return(MLX_FAIL);
	if((env->img = ft_new_image(env, env->width, env->height)) == NULL)
		return (IMG_FAIL);
	if ((error = ft_init(env)) != SUCCESS)
		return(error);
	return (SUCCESS);

}
