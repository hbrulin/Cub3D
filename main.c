/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/23 19:45:20 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_check_cub(char *s)
{
	int len;

	len = ft_strlen(s) - 1;
	if (s[len] != 'b')
		return (INVALID_ARG);
	if (s[len - 1] != 'u')
		return (INVALID_ARG);
	if (s[len - 2] != 'c')
		return (INVALID_ARG);
	if (s[len - 3] != '.')
		return (INVALID_ARG);
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	if ((argc != 2 && argc != 3) || ft_check_cub(argv[1]) == INVALID_ARG)
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
