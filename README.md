# Cub3D

COMPILATEUR QUI MARCHE gcc obj/main.o obj/parser.o -L minilibx_opengl -l mlx libft/libft.a -framework OpenGL -framework AppKit

	/*unsigned char r;
  	unsigned char g;
  	unsigned char b;
	
	//faire une regle pour changer si big endian?
	r = (color & 0xFF00000) >> 16;
  	g = (color & 0xFF000) >> 8;
  	b = (color & 0xFF);

	//bonne couleur mais mauvais emplacement
	img->img_data[(p_y * img->size_line) * p_x + img->bpp] = b;
	img->img_data[(p_y * img->size_line) * p_x + img->bpp + 1] = g; 
	img->img_data[(p_y * img->size_line) * p_x + img->bpp + 2] = r;*/
