/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 17:41:43 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
 	t_env	env;
 	int		error;
	init_var(&env);
 	if (argc != 2 && argc != 3)
 		return (ft_error(INVALID_ARG, &env));
	if (argc == 3 && (ft_strncmp(argv[2], "-save", ft_strlen(argv[2])) == 0))
		env.flag_save = 1;
	else if (argc == 3)
		return (ft_error(INVALID_ARG, &env));
 	if((error = get_map(&env, argv[1])) != SUCCESS)
 		return (ft_error(error, &env));
 	if((error = ft_parser(&env)) != SUCCESS)
 		return (ft_error(error, &env));
 	if((error = init_env(&env)) != SUCCESS)
 		return (ft_error(error, &env));	
	if (env.flag_save == 1)
	{
		ft_disp_screen(&env);
		if ((error = ft_save(&env)) != SUCCESS)
			return(error);
		deal_exit(&env);
		return (SAVE);
	}
 	if ((error = events(&env)) != SUCCESS)
		return (ft_error(error, &env));
    return (SUCCESS);
}
