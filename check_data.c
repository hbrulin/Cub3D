/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 10:20:46 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/22 10:38:17 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_bet_rgb(char *s, int i)
{
	i++;
	while ((ft_isdigit(s[i]) != 1))
	{
		if(s[i] != ' ')
			return (WRONG_INPUT);
		i++;
	}
	return(SUCCESS);
}

int		check_data_two(t_env *env)
{
	int i;

	i = 1;
	while (env->data.f[i])
	{
		if (ft_isalpha(env->data.f[i]))
			return (WRONG_INPUT);
		if(env->data.f[i] == ',')
		{
			if (check_bet_rgb(env->data.f, i) != SUCCESS)
				return (WRONG_INPUT);
		}
		i++;
	}
	i = 1;
	while (env->data.c[i])
	{
		if (ft_isalpha(env->data.c[i]))
			return (WRONG_INPUT);
		if(env->data.c[i] == ',')
		{
			if (check_bet_rgb(env->data.c, i) != SUCCESS)
				return (WRONG_INPUT);
		}
		i++;
	}
	return(SUCCESS);
}

int		check_data(t_env *env)
{
	int i;

	if (!env->data.r || !env->data.n || !env->data.s || !env->data.w ||
		!env->data.e || !env->data.sp || !env->data.f || !env->data.c ||
		!env->map.list)
		return (WRONG_INPUT);
	i = 1;
	while (env->data.r[i])
	{
		if (ft_isalpha(env->data.r[i]))
			return (WRONG_INPUT);
		i++;
	}
	if (check_data_two(env) != SUCCESS)
		return(WRONG_INPUT);
	return (SUCCESS);
}
