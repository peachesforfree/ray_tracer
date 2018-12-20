#include "../includes/ray_tracer.h"

void		mlx_start(t_mlx *env)
{
	if (!(env->mlx = mlx_init()))
	{
		printf("\nSTART UP ERROR: FAILED TO INITIALIZE MLX\n");
		exit(0);
	}
	else if (!(env->win = mlx_new_window(env->mlx, WIN_X, WIN_Y, "Testing")))
	{
		printf("\nSTART UP ERROR: FAILED TO INITIALIZE WINDOW\n");
		exit(0);
	}
	else if (!(env->img_ptr = mlx_new_image(env->mlx, WIN_X, WIN_Y)))
	{
		printf("\nSTART UP ERROR: FAILED TO INIZIALIZE IMAGE\n");
		exit(0);
	}
	else if (!(env->img = mlx_get_data_addr(env->img_ptr, &env->bpp,
					&env->size_line, &env->endian)))
	{
		printf("\nSTART UP ERROR: FAILED TO INIZIALIZE IMG PTR\n");
		exit(0);
	}
}