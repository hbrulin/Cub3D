/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:48:09 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 19:42:28 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

char	*ft_strcpy_no_space(char *dst, const char *src)
{
	int i;
	int j;
	int len;

	len = ft_strlen(src);
	i = 0;
	j = 0;
	while (i <= len)
	{
		if (src[i] != ' ')
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	return (dst);
}

char	*ft_strdup_no_space(const char *s)
{
	int		s_len;
	char	*dst;
	int i;
	int count;

	i = 0;
	count = 0;
	while(s[i])
	{
		if (s[i] == ' ')
			count++;
		i++;
	}
	s_len = ft_strlen(s) - count;
	if (!(dst = (char *)malloc(sizeof(char) * s_len + 1)))
		return (NULL);
	ft_strcpy_no_space(dst, s);
	dst[s_len] = '\0';
	return (dst);
}

t_img	*ft_new_image(t_env *env, int width, int height)
{
	t_img *img; 
	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	if(!(img->img_ptr = mlx_new_image (env->mlx_ptr, width, height)))
		return (NULL);
	if(!(img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian)))
		return (NULL);
	img->width = width;
	img->height = height;
	return (img);
}

t_tex	*ft_new_tex(t_env *env, char *file)
{
	t_tex *tex;
	if (!(tex = malloc(sizeof(t_tex))))
		return (NULL);
	if(!(tex->tex_ptr = mlx_xpm_file_to_image(env->mlx_ptr, file, &tex->width, &tex->height)))
		return (NULL);
	if(!(tex->tex_data = (int *)mlx_get_data_addr(tex->tex_ptr, &tex->bpp, &tex->size_line, &tex->endian)))
		return (NULL);
	return (tex);
}
