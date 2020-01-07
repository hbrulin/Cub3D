/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/07 16:02:58 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //remove

int main(int argc, char **argv)
{
 	t_env env;
 	int		error;
 	if (argc == 1)
 		return (NO_MAP);
 	if((error = get_map(&env, argv[1])) != SUCCESS)
 		return (error);
 	if((error = ft_parser(&env)) != SUCCESS)
 		return (error);
 	if((error = init_env(&env)) != SUCCESS)
 		return (error);
 	events(&env);
    return (SUCCESS);
}


