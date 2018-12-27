#include "../includes/ray_tracer.h"

#define SPHERE      1
#define CONE        2
#define TRIANGLE    3
#define CYLINDER    4

/*
**Given the ray and the objects linked list

    update below function to the new C syntax
    and need to include and write the 

    world->hit(r, 0.0, MAXFLOAT, rec)
        which will cycle thru the linked list and check the object with its appropriate hit function
*/

t_vec3      color(t_ray *ray, t_hit_list *world)
{
    t_hit_record    rec;

    if (world->hit(r, 0.0, MAXFLOAT, rec))
    {
        return (0.5*(unit_direction.y() + 1.0);
    }
    //else
    vec 3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(void)
{
    t_mlx   mlx;
    
    mlx_start(&mlx);
    int *array;
    array = mlx.img;


    t_vec3  lower_left_corner;
    set_vec(&lower_left_corner, -2.0, -1.0, -1.0);
    t_vec3  horizontal;
    set_vec(&horizontal, 4.0, 0.0, 0.0);
    t_vec3  vertical;
    set_vec(&vertical, 0.0, 2.0, 0.0);
    t_vec3  origin;
    set_vec(&origin, 0.0, 0.0, 0.0);

    t_hit_list      *world;
    world = new_hit_list();

    int j;
    int i;
    float u;
    float v;
    t_ray   r;
    t_vec3  pixel;
    size_t  counter;

    counter = 0;
    j = WIN_Y-1;
    while (j >= 0)
    {
        i = 0;
        v = (float)(j)/(float)(WIN_Y);
        while (i < WIN_X)
        {
            u = (float)(i) / (float)(WIN_X);
            //-1,1 translation and scaling(transformation) for camera
            r = new_ray(origin, v_plus_v(lower_left_corner, v_plus_v(v_mult_f(u, horizontal), v_mult_f(v, vertical))));
            

            pixel = color(&r, world);
            int ir = (int)(255.99 * pixel.e[0]);
            int ig = (int)(255.99 * pixel.e[1]);
            int ib = (int)(255.99 * pixel.e[2]);
            array[counter++] = ft_rgb(ir, ig, ib);
            i++;
        }
        j--;
    }

	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img_ptr, 0, 0);
    mlx_loop(mlx.mlx);
    return (0);
}



// gcc -Wall -Wextra -Werror -I libs/minilibx -L libs/minilibx -lmlx -framework OpenGL -framework AppKit sources/main.c
/*      make struct where
            int     id;
            void    *ptr;
            int     (*hit)();
            strct   *next;

because each item type has a special ray intercept equation. That will be referenced in int(*hit)() and (struct)
beacuse the function is assigned in advanced, no need to change or cast in the process.


*/