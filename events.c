/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:24:23 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/09 13:50:46 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

int	deal_key(int key, t_env *env)
{
	//ft_putnbr_fd(key, 1);

	if (key == KEY_ESCAPE)
	{
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		mlx_destroy_image(env->mlx_ptr, env->img->img_ptr);
		exit(0);
	}
	return (key);
}

//pour la croix et force quit
int	deal_exit(t_env *env)
{
	mlx_destroy_image(env->mlx_ptr, env->img->img_ptr);
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	exit(0);
	// + il faut bien tout free et destroy etc....
}

int	ft_key_hit	(int key, t_env *env)
{
	if (key == KEY_UP || key == KEY_W)
		env->up = 1;
	if (key == KEY_DOWN || key == KEY_S)
		env->down = 1;
	if (key == KEY_LEFT)
		env->left = 1;
	if (key == KEY_A)
		env->strafl = 1;
	if (key == KEY_RIGHT)
		env->right = 1; 
	if (key == KEY_D)
		env->strafr = 1;
	return (SUCCESS);
}

int		ft_key_release(int key, t_env *env)
{
	if (key == KEY_UP || key == KEY_W)
		env->up = 0;
	if (key == KEY_DOWN || key == KEY_S)
		env->down = 0;
	if (key == KEY_LEFT)
		env->left = 0;
	if (key == KEY_A)
		env->strafl = 0;
	if (key == KEY_RIGHT)
		env->right = 0; 
	if (key == KEY_D)
		env->strafr = 0;
	return (0);
}

int		ft_run(t_env *env)
{
	mlx_destroy_image(env->mlx_ptr, env->img->img_ptr);
	if((env->img = ft_new_image(env, env->width, env->height)) == NULL)
		return (IMG_FAIL); //ou juste mlx new img??
	ft_move(env);
	ft_disp_screen(env);
	mlx_put_image_to_window (env->mlx_ptr, env->win_ptr, env->img->img_ptr, 0, 0);
	return (0);
}


void	events(t_env *env)
{
	mlx_key_hook (env->win_ptr, deal_key, env);
	mlx_hook(env->win_ptr, 17, StructureNotifyMask, deal_exit, env);
	mlx_hook(env->win_ptr, KEYPRESS, KEYPRESSMASK, ft_key_hit, env);
	mlx_hook(env->win_ptr, KEYRELEASE, KEYRELEASEMASK, ft_key_release, env);
	mlx_loop_hook(env->mlx_ptr, ft_run, env);
	mlx_loop(env->mlx_ptr);
}
