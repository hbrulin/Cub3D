/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:05:41 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 19:44:34 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	pixel_tex(t_tex *tex, t_env *env)
{
	env->color = tex->tex_data[tex->width * env->tex.y + env->tex.x];
}

void	pix_color(t_env *env)
{
	if (env->wall == 0)
	{
		if (env->step.x < 0)
			pixel_tex(env->tex1, env);
		else
			pixel_tex(env->tex2, env);
	}
	else
	{
		if (env->step.y > 0)
			pixel_tex(env->tex3, env);
		else
			pixel_tex(env->tex4, env);
	}
}

int		get_color(t_color *color, char *s)
{
	int		i;
	char	**tab;

	i = 0;
	while (!ft_isdigit(s[i]))
		i++;
	if (!(tab = ft_split(s + i, ',')))
		return (MALLOC_FAIL);
	if (tab_size(tab) == 3)
	{
		color->rgb.r = ft_atoi(tab[0]);
		color->rgb.g = ft_atoi(tab[1]);
		color->rgb.b = ft_atoi(tab[2]);
		color->rgb.a = 0x00;
	}
	else
	{
		ft_tabdel((void **)tab);
		return (WRONG_INPUT);
	}
	ft_tabdel((void **)tab);
	return (SUCCESS);
}
