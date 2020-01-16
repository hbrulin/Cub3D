/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:40:42 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 18:17:10 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_flag_save(t_env *env, int argc, char *s)
{
	if (argc == 3 && (ft_strncmp(s, "-save", ft_strlen(s)) == 0))
		env->flag_save = 1;
	else if (argc == 3)
		return (INVALID_ARG);
	return (SUCCESS);
}

int	init_var(t_env *env, char *s)
{
	int error;

	env->speed = 0.1;
	if((error = get_map(env, s)) != SUCCESS)
 		return (error);
 	if((error = ft_parser(env)) != SUCCESS)
 		return (error);
	if((error = init_env(env)) != SUCCESS)
 		return (error);	

	return (SUCCESS);
}
