/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/14 18:45:35 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //remove

int ft_error(int error, t_env *env)
{
	if (error == INVALID_ARG)
		ft_putstr("Error\n Invalid arguments");
	if (error == WRONG_MAP)
		ft_putstr("Error\n Invalid map");
	if (error == MALLOC_FAIL)
		ft_putstr("Error\n Memory allocation has failed");
	if (error == OPEN_ERR)
		ft_putstr("Error\n File could not be opened");
	if (error == IMG_FAIL)
		ft_putstr("Error\n Image could not be allocated");
	if (error == MLX_FAIL)
		ft_putstr("Error\n Mlx failure");
	if (error == MLX_FAIL)
		ft_putstr("Error\n Writing in bmp has failed");
	deal_exit(env);
	return (error);
}

int main(int argc, char **argv)
{
 	t_env env;
 	int		error;
 	if (argc != 2 && argc != 3)
 		return (ft_error(INVALID_ARG, &env));
 	if((error = get_map(&env, argv[1])) != SUCCESS)
 		return (ft_error(error, &env));
 	if((error = ft_parser(&env)) != SUCCESS)
 		return (ft_error(error, &env));
 	if((error = init_env(&env)) != SUCCESS)
 		return (ft_error(error, &env));
	if (argc == 3 && (ft_strncmp(argv[2], "-save", ft_strlen(argv[2])) == 0))
		env.flag_save = 1;
 	if ((error = events(&env)) != SUCCESS)
		return (ft_error(error, &env));
    return (SUCCESS);
}


