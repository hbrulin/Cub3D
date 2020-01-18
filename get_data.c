/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 20:14:50 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 15:41:05 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int		check_data(t_env *env)
{
	if (!env->data.r || !env->data.n || !env->data.s || !env->data.w ||
		!env->data.e || !env->data.sp || !env->data.f || !env->data.c ||
		!env->map.list)
		return (WRONG_INPUT);
	if (env->data.r[1] != ' ' || env->data.n[2] != ' ' || env->data.s[2] != ' '
		|| env->data.w[2] != ' ' || env->data.e[2] != ' ' ||
		env->data.sp[1] != ' ' || env->data.f[1] != ' ' ||
		env->data.c[1] != ' ')
		return (WRONG_INPUT);
	return (SUCCESS);
}

int		get_data_four(t_env *env, char *line, int i, int *flag_map)
{
	if (line[i] == 'F' && line[i + 1] == ' ' && *flag_map == 0 &&
		env->data.f == NULL)
	{
		if (!(env->data.f = ft_strtrim(line + i, " ")))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'F' && line[i + 1] == ' ' && (flag_map != 0 ||
		env->data.f != NULL))
		return (WRONG_INPUT);
	if (line[i] == 'C' && line[i + 1] == ' ' && *flag_map == 0 &&
		env->data.c == NULL)
	{
		if (!(env->data.c = ft_strtrim(line + i, " ")))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'C' && line[i + 1] == ' ' && (flag_map != 0 ||
		env->data.c != NULL))
		return (WRONG_INPUT);
	return (SUCCESS);
}

int		get_data_three(t_env *env, char *line, int i, int *flag_map)
{
	if (line[i] == 'E' && line[i + 1] == 'A' && *flag_map == 0 &&
		env->data.e == NULL)
	{
		if (!(env->data.e = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A' && (flag_map != 0 ||
		env->data.e != NULL))
		return (WRONG_INPUT);
	if (line[i] == 'S' && line[i + 1] == ' ' && *flag_map == 0 &&
		env->data.sp == NULL)
	{
		if (!(env->data.sp = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'S' && line[i + 1] == ' ' && (flag_map != 0 ||
		env->data.sp != NULL))
		return (WRONG_INPUT);
	if ((env->error = get_data_four(env, line, i, flag_map)) != SUCCESS)
		return (env->error);
	return (SUCCESS);
}

int		get_data_two(t_env *env, char *line, int i, int *flag_map)
{
	if (line[i] == 'S' && line[i + 1] == 'O' && *flag_map == 0 &&
		env->data.s == NULL)
	{
		if (!(env->data.s = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O' && (*flag_map != 0 ||
		env->data.s != NULL))
		return (WRONG_INPUT);
	if (line[i] == 'W' && line[i + 1] == 'E' && *flag_map == 0
		&& env->data.w == NULL)
	{
		if (!(env->data.w = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E' && (flag_map != 0 ||
		env->data.w != NULL))
		return (WRONG_INPUT);
	if ((env->error = get_data_three(env, line, i, flag_map)) != SUCCESS)
		return (env->error);
	return (SUCCESS);
}

int		get_data(t_env *env, char *line, int i, int *flag_map)
{
	if (line[i] == 'R' && *flag_map == 0 && env->data.r == NULL)
	{
		if (!(env->data.r = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'R' && (*flag_map != 0 || env->data.r != NULL))
		return (WRONG_INPUT);
	if (line[i] == 'N' && line[i + 1] == 'O' && *flag_map == 0 &&
		env->data.n == NULL)
	{
		if (!(env->data.n = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'N' && line[i + 1] == 'O' && (*flag_map != 0 ||
		env->data.n != NULL))
		return (WRONG_INPUT);
	if ((env->error = get_data_two(env, line, i, flag_map)) != SUCCESS)
		return (env->error);
	return (SUCCESS);
}
