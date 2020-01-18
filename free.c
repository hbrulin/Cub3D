/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:26:33 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 15:42:55 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_tex(t_env *env, t_tex *tex)
{
	if (tex)
	{
		mlx_destroy_image(env->mlx_ptr, tex->tex_ptr);
		free(tex);
		tex = NULL;
	}
}

void	ft_free_img(t_env *env)
{
	if (env->img)
	{
		mlx_destroy_image(env->mlx_ptr, env->img->img_ptr);
		free(env->img);
		env->img = NULL;
	}
}

void	ft_free_tabs(t_env *env)
{
	if (env->rc.zbuffer)
		free(env->rc.zbuffer);
	if (env->map.tab_map)
		ft_tabdel((void *)env->map.tab_map);
	if (env->data.r)
		free(env->data.r);
	if (env->data.no)
		free(env->data.no);
	if (env->data.so)
		free(env->data.so);
	if (env->data.we)
		free(env->data.we);
	if (env->data.ea)
		free(env->data.ea);
	if (env->data.f)
		free(env->data.f);
	if (env->data.c)
		free(env->data.c);
	if (env->data.spr)
		free(env->data.spr);
}
