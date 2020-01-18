/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 20:18:17 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 15:52:04 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	if (!(env->data.no = ft_strtrim(env->data.n + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.n);
	i = get_start_path(env->data.s);
	if (!(env->data.so = ft_strtrim(env->data.s + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.s);
	i = get_start_path(env->data.w);
	if (!(env->data.we = ft_strtrim(env->data.w + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.w);
	i = get_start_path(env->data.e);
	if (!(env->data.ea = ft_strtrim(env->data.e + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.e);
	i = get_start_path(env->data.sp);
	if (!(env->data.spr = ft_strtrim(env->data.sp + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.sp);
	return (SUCCESS);
}
