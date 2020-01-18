/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:05:41 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 15:12:53 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	pixel_tex(t_tex *tex, t_env *env)
{
	env->color = tex->tex_data[tex->width * env->rc.tex.y + env->rc.tex.x];
}

void	pix_color(t_env *env)
{
	if (env->rc.wall == 0)
	{
		if (env->rc.step.x < 0)
			pixel_tex(env->tex1, env);
		else
			pixel_tex(env->tex2, env);
	}
	else
	{
		if (env->rc.step.y > 0)
			pixel_tex(env->tex3, env);
		else
			pixel_tex(env->tex4, env);
	}
}

int		check_color(char **tab)
{
	int r;
	int g;
	int b;

	if (tab_size(tab) == 3)
	{
		r = ft_atoi(tab[0]);
		g = ft_atoi(tab[1]);
		b = ft_atoi(tab[2]);
	}
	else
	{
		ft_tabdel((void **)tab);
		return (WRONG_INPUT);
	}
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (WRONG_INPUT);
	return (SUCCESS);
}

int		get_color(t_color *color, char *s)
{
	int		i;
	char	**tab;

	i = 0;
	while (!ft_isdigit(s[i]) && s[i] != '-')
		i++;
	if (!(tab = ft_split(s + i, ',')))
		return (MALLOC_FAIL);
	if (check_color(tab) == WRONG_INPUT)
		return (WRONG_INPUT);
	color->rgb.r = ft_atoi(tab[0]);
	color->rgb.g = ft_atoi(tab[1]);
	color->rgb.b = ft_atoi(tab[2]);
	color->rgb.a = 0x00;
	ft_tabdel((void **)tab);
	return (SUCCESS);
}
