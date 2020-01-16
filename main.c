/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 15:20:28 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//file init.c
void	init_var(t_env *env)
{
	env->mlx_ptr = NULL;
	env->win_ptr = NULL;
	env->img = NULL;
	env->tab_sprite = NULL;
	env->tex1 = NULL;
	env->tex2 = NULL;
	env->tex3 = NULL;
	env->tex4 = NULL;
	env->sprite = NULL;
	env->zbuffer = NULL;
	env->sp_order = NULL;
	env->sp_distance = NULL;
	env->map.tab_map = NULL; 
	env->map.list = NULL;
	env->flag_save = 0;
	env->speed = 0.1;
	env->move.up = 0;
	env->move.down = 0;
	env->move.left = 0;
	env->move.right = 0;
	env->move.strafl = 0;
	env->move.strafr = 0;
	
	//suppr si pas necessaire
	env->tex_x = 0;
	env->tex_y = 0;
	env->step_tex = 0;
	env->tex_pos = 0;

		//necessaire si 0 sprite?
	/*env->sp.spcamx = 0;
	env->sp.spcamy = 0;
	env->sp.transx = 0;
	env->sp.transy = 0;
	env->sp.spriteScreenX = 0;
	env->sp.spriteHeight = 0;
	env->sp.drawStartY = 0;
	env->sp.drawEndY = 0;
	env->sp.spriteWidth = 0;
	env->sp.drawStartX = 0;
	env->sp.drawEndX = 0;*/
	
	
	//+data set NULL??
}

int ft_error(int error, t_env *env)
{
	if (error == INVALID_ARG)
		ft_putstr("Error\n Invalid argument");
	if (error == WRONG_INPUT)
		ft_putstr("Error\n Invalid input");
	if (error == WRONG_MAP)
		ft_putstr("Error\n Invalid map");
	if (error == WRONG_MAP)
		ft_putstr("Error\n Invalid input");
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
	if (error == WRONG_TEX)
		ft_putstr("Error\n Wrong path for texture");
	deal_exit(env);
	return (error);
}

int main(int argc, char **argv)
{
 	t_env env;
 	int		error;
	init_var(&env);
 	if (argc != 2 && argc != 3)
 		return (ft_error(INVALID_ARG, &env));
	if (argc == 3 && (ft_strncmp(argv[2], "-save", ft_strlen(argv[2])) == 0))
		env.flag_save = 1;
	else if(argc == 3)
		return (ft_error(INVALID_ARG, &env));
 	if((error = get_map(&env, argv[1])) != SUCCESS)
 		return (ft_error(error, &env));
 	if((error = ft_parser(&env)) != SUCCESS)
 		return (ft_error(error, &env));
 	if((error = init_env(&env)) != SUCCESS)
 		return (ft_error(error, &env));
 	if ((error = events(&env)) != SUCCESS)
		return (ft_error(error, &env));
    return (SUCCESS);
}


