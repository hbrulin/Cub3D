/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:40:42 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 14:19:50 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_tex(t_env *env)
{
	if ((env->tex1 = ft_new_tex(env, env->data.NO)) == NULL)
		return (WRONG_TEX);
	if ((env->tex2 = ft_new_tex(env, env->data.SO)) == NULL)
		return (WRONG_TEX);
	if ((env->tex3 = ft_new_tex(env, env->data.EA)) == NULL)
		return (WRONG_TEX);
	if ((env->tex4 = ft_new_tex(env, env->data.WE)) == NULL)
		return (WRONG_TEX);
	if ((env->sprite = ft_new_tex(env, env->data.SP)) == NULL)
		return (WRONG_TEX);
	return (SUCCESS);
}

int		get_res(t_env *env)
{
	int		i;
	char	**tab;

	i = 0;
	while (!ft_isdigit(env->data.R[i]))
		i++;
	if (!(tab = ft_split(env->data.R + i, ' ')))
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
	return (SUCCESS);
}

int		init_flag_save(t_env *env, int argc, char *s)
{
	if (argc == 3 && (ft_strncmp(s, "-save", ft_strlen(s)) == 0))
		env->flag_save = 1;
	else if (argc == 3)
		return (INVALID_ARG);
	return (SUCCESS);
}

int		init_var(t_env *env, char *s)
{
	env->rc.speed = 0.1;
	if ((env->error = get_map(env, s)) != SUCCESS)
		return (env->error);
	if ((env->error = ft_parser(env)) != SUCCESS)
		return (env->error);
	if ((env->error = get_color(&env->color_floor, env->data.F)) != SUCCESS)
		return (env->error);
	if ((env->error = get_color(&env->color_ceiling, env->data.C)) != SUCCESS)
		return (env->error);
	if ((env->error = get_res(env)) != SUCCESS)
		return (env->error);
	if ((env->error = init_env_pos(env)) != SUCCESS)
		return (env->error);
	if (!(env->rc.zbuffer = malloc(sizeof(double) * env->width)))
		return (MALLOC_FAIL);
	if ((env->error = init_tex(env)) != SUCCESS)
		return (env->error);
	return (SUCCESS);
}
