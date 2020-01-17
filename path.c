/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 20:18:17 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/17 20:24:59 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	ft_free_path(char *s)
{
	free(s);
	s = NULL;
}

int		get_start_path(char *s)
{
	int i;

	i = 0;
	while (s[i] != '.')
		i++;
	return (i);
}

int		path_fix(t_env *env)
{
	int i;

	i = get_start_path(env->data.n);
	if (!(env->data.NO = ft_strtrim(env->data.n + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.n);
	i = get_start_path(env->data.s);
	if (!(env->data.SO = ft_strtrim(env->data.s + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.s);
	i = get_start_path(env->data.w);
	if (!(env->data.WE = ft_strtrim(env->data.w + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.w);
	i = get_start_path(env->data.e);
	if (!(env->data.EA = ft_strtrim(env->data.e + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.e);
	i = get_start_path(env->data.sp);
	if (!(env->data.SP = ft_strtrim(env->data.sp + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.sp);
	return (SUCCESS);
}
