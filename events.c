/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:24:23 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 15:37:05 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"

int		deal_exit(t_env *env)
{
	ft_free_tabs(env);
	ft_free_img(env);
	ft_free_tex(env, env->tex1);
	ft_free_tex(env, env->tex2);
	ft_free_tex(env, env->tex3);
	ft_free_tex(env, env->tex4);
	ft_free_tex(env, env->sprite);
	if (env->win_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	if (env->mlx_ptr)
		free(env->mlx_ptr);
	exit(0);
}

int		ft_key_hit(int key, t_env *env)
{
	if (key == KEY_UP || key == KEY_W)
		env->move.up = 1;
	if (key == KEY_DOWN || key == KEY_S)
		env->move.down = 1;
	if (key == KEY_LEFT)
		env->move.left = 1;
	if (key == KEY_A)
		env->move.strafl = 1;
	if (key == KEY_RIGHT)
		env->move.right = 1;
	if (key == KEY_D)
		env->move.strafr = 1;
	if (key == KEY_ESCAPE)
		deal_exit(env);
	return (SUCCESS);
}

int		ft_key_release(int key, t_env *env)
{
	if (key == KEY_UP || key == KEY_W)
		env->move.up = 0;
	if (key == KEY_DOWN || key == KEY_S)
		env->move.down = 0;
	if (key == KEY_LEFT)
		env->move.left = 0;
	if (key == KEY_A)
		env->move.strafl = 0;
	if (key == KEY_RIGHT)
		env->move.right = 0;
	if (key == KEY_D)
		env->move.strafr = 0;
	return (SUCCESS);
}

int		ft_run(t_env *env)
{
	ft_free_img(env);
	if ((env->img = ft_new_image(env, env->width, env->height)) == NULL)
		return (IMG_FAIL);
	ft_move(env);
	ft_disp_screen(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img->img_ptr, 0,
		0);
	return (SUCCESS);
}

int		events(t_env *env)
{
	if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->width, env->height,
		"Cub3D")))
		return (MLX_FAIL);
	mlx_hook(env->win_ptr, 17, STRUCTURENOTIFYMASK, deal_exit, env);
	mlx_hook(env->win_ptr, KEYPRESS, KEYPRESSMASK, ft_key_hit, env);
	mlx_hook(env->win_ptr, KEYRELEASE, KEYRELEASEMASK, ft_key_release, env);
	if ((env->error = mlx_loop_hook(env->mlx_ptr, ft_run, env)) != SUCCESS)
		return (env->error);
	mlx_loop(env->mlx_ptr);
	return (SUCCESS);
}
