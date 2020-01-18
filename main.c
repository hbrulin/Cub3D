/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 15:53:00 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	if (argc != 2 && argc != 3)
		return (ft_error(INVALID_ARG, &env));
	if ((env.error = init_flag_save(&env, argc, argv[2])) != SUCCESS)
		return (ft_error(env.error, &env));
	if ((env.error = init_var(&env, argv[1])) != SUCCESS)
		return (ft_error(env.error, &env));
	if (env.flag_save == 1)
	{
		if ((env.error = launch_save(&env)) != SUCCESS)
			return (ft_error(env.error, &env));
		return (SUCCESS);
	}
	if ((env.error = events(&env)) != SUCCESS)
		return (ft_error(env.error, &env));
	return (SUCCESS);
}
