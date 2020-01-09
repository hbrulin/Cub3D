/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/09 14:13:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //remove

int main(int argc, char **argv)
{
 	t_env env;
 	int		error;
 	if (argc != 2 && argc != 3)
 		return (NO_MAP);
 	if((error = get_map(&env, argv[1])) != SUCCESS)
 		return (error);
 	if((error = ft_parser(&env)) != SUCCESS)
 		return (error);
 	if((error = init_env(&env)) != SUCCESS)
 		return (error);
	if (argc == 3 && ft_strcmp(argv[2], "-save"))
		ft_save();
 	events(&env);
    return (SUCCESS);
}


