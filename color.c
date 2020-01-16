/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:05:41 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 12:14:24 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	get_color(t_env *env, t_color *color_floor, t_color *color_ceiling)
{
	int i;
	char **tab;

	i = 0;
	while (!ft_isdigit(env->data.F[i]))
		i++;
	if(!(tab = ft_split(env->data.F + i, ',')))
		return (MALLOC_FAIL);
	if (tab_size(tab) == 3)
	{
		color_floor->rgb.r = ft_atoi(tab[0]);
		color_floor->rgb.g = ft_atoi(tab[1]);
		color_floor->rgb.b = ft_atoi(tab[2]);
		color_floor->rgb.a = 0x00;
	}
	else 
	{
		ft_tabdel((void **)tab);
		return (WRONG_INPUT);
	}
	ft_tabdel((void **)tab); //attention possible leak ici avec mon split

	//c'est quoi cette condition
	if ((!color_floor->rgb.r && color_floor->rgb.r != 0) || (!color_floor->rgb.g && color_floor->rgb.g != 0) || (!color_floor->rgb.b && color_floor->rgb.b != 0)) //autre chose a verifier quand a mauvais input (genre si pas de virgule entre les valeurs dans le doc map)
		return (WRONG_INPUT);
	if (color_floor->rgb.r > 255 || color_floor->rgb.r < 0 || color_floor->rgb.g > 255 || color_floor->rgb.g < 0 || color_floor->rgb.b > 255 || color_floor->rgb.b < 0 )
		return (WRONG_INPUT);

	i = 0;
	while (!ft_isdigit(env->data.C[i]))
		i++;
	if(!(tab = ft_split(env->data.C + i, ','))) // quid si pas de virgule???
		return (MALLOC_FAIL);
	if (tab_size(tab) == 3)
	{
		color_ceiling->rgb.r = ft_atoi(tab[0]);
		color_ceiling->rgb.g = ft_atoi(tab[1]);
		color_ceiling->rgb.b = ft_atoi(tab[2]);
		color_ceiling->rgb.a = 0x00;
	}
	else 
	{
		ft_tabdel((void **)tab);
		return (WRONG_INPUT);
	}
	ft_tabdel((void **)tab); //attention possible leak ici avec mon split
	
	//c'est quoi cette condition??
	if ((!color_ceiling->rgb.r && color_ceiling->rgb.r != 0) || (!color_ceiling->rgb.g && color_ceiling->rgb.g != 0) || (!color_ceiling->rgb.b && color_ceiling->rgb.b != 0))
		return (WRONG_INPUT);
	if (color_ceiling->rgb.r > 255 || color_ceiling->rgb.r < 0 || color_ceiling->rgb.g > 255 || color_ceiling->rgb.g < 0 || color_ceiling->rgb.b > 255 || color_ceiling->rgb.b < 0 )
		return (WRONG_INPUT);
	
	return (SUCCESS);
}
