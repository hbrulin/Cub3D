/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/11 13:06:10 by hbrulin          ###   ########.fr       */
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
	if (argc == 3 && (ft_strncmp(argv[2], "-save", ft_strlen(argv[2])) == 0))
		env.flag_save = 1;
 	events(&env);
    return (SUCCESS);
}


