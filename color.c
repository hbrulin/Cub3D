/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:05:41 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/07 15:52:16 by hbrulin          ###   ########.fr       */
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
	color_floor->rgb.r = ft_atoi(tab[0]);
	color_floor->rgb.g = ft_atoi(tab[1]);
	color_floor->rgb.b = ft_atoi(tab[2]);
	ft_tabdel((void **)tab); //attention possible leak ici avec mon split, verifier mon tabdel

	//verifier aussi que rgb < 255
	if ((!color_floor->rgb.r && color_floor->rgb.r != 0) || (!color_floor->rgb.g && color_floor->rgb.g != 0) || (!color_floor->rgb.b && color_floor->rgb.b != 0)) //autre chose a verifier quand a mauvais input (genre si pas de virgule entre les valeurs dans le doc map)
	{
		ft_putstr("Wrong floor color");
		return (WRONG_INPUT);
	}

	i = 0;
	while (!ft_isdigit(env->data.C[i]))
		i++;
	if(!(tab = ft_split(env->data.C + i, ',')))
		return (MALLOC_FAIL);
	color_ceiling->rgb.r = ft_atoi(tab[0]);
	color_ceiling->rgb.g = ft_atoi(tab[1]);
	color_ceiling->rgb.b = ft_atoi(tab[2]);
	ft_tabdel((void **)tab); //attention possible leak ici avec mon split, verifier mon tabdel
	
	//verifier aussi que rgb < 255
	if ((!color_ceiling->rgb.r && color_ceiling->rgb.r != 0) || (!color_ceiling->rgb.g && color_ceiling->rgb.b != 0) || (!color_ceiling->rgb.b && color_ceiling->rgb.b != 0))//autre chose a verifier quand a mauvais input (genre si pas de virgule entre les valeurs dans le doc map)
	{
		ft_putstr("Wrong ceiling color");
		return (WRONG_INPUT);
	}
	return (SUCCESS);
}
