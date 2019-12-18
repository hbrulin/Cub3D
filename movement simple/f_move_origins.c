//avec tab_pos tableau de INT

void	ft_y_down(t_env *env)
{
	int x;
	int y;

	x = env->map.tab_pos[0];
	y = env->map.tab_pos[1];

	if (env->map.tab_map[y - 1][x] == '0')
	{
		env->map.tab_map[y - 1][x] = env->map.player;
		env->map.tab_map[y][x] = '0';
		env->map.tab_pos[1] = y - 1;
	}
}

void	ft_y_up(t_env *env)
{
	int x;
	int y;

	x = env->map.tab_pos[0];
	y = env->map.tab_pos[1];

	if (env->map.tab_map[y + 1][x] == '0')
	{
		env->map.tab_map[y + 1][x] = env->map.player;
		env->map.tab_map[y][x] = '0';
		env->map.tab_pos[1] = y + 1;
	}
}

void	ft_x_down(t_env *env)
{
	int x;
	int y;

	x = env->map.tab_pos[0];
	y = env->map.tab_pos[1];

	if (env->map.tab_map[y][x - 1] == '0')
	{
		env->map.tab_map[y][x - 1] = env->map.player;
		env->map.tab_map[y][x] = '0';
		env->map.tab_pos[0] = x - 1;
	}
}

void	ft_x_up(t_env *env)
{
	int x;
	int y;

	x = env->map.tab_pos[0];
	y = env->map.tab_pos[1];

	if (env->map.tab_map[y][x + 1] == '0')
	{
		env->map.tab_map[y][x + 1] = env->map.player;
		env->map.tab_map[y][x] = '0';
		env->map.tab_pos[0] = x + 1;
	}
}
