#include "../includes/ray_tracer.h"

#define SPHERE      1
#define CONE        2
#define TRIANGLE    3
#define CYLINDER    4

/*
    Given world list, ray, min/max, and &t_hit_record

    we cycle throug the linked list, given the function pointer in the linked list, we input
        ray, t_min, closest_so_far, temp_rec, and the world object
    this function in the list determines if the ray intercepts the object.

    closest_so_far limits the ray length for potential objects further from the last found object intercept

*/

int hitable_list_hit(const t_ray *r, float t_min, float t_max, t_hit_record *rec, t_hit_list *world)
{
    t_hit_record temp_rec;
    int hit_anything;
    double closest_so_far;

    hit_anything = 0;
    closest_so_far = t_max;
    while(world != NULL)
    {
        if (world->hit(r, t_min, closest_so_far, temp_rec, &world->object))   //here we use the hit function in the linked list
        {                                                                     //need to figure out how to package data to fit into norme
            hit_anything = 1;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
        world = world->next;
    }
    return (hit_anything);
}

/*
**Given the ray and the objects linked list
    world->hit(r, 0.0, MAXFLOAT, rec)
        which will cycle thru the linked list and check the object with its appropriate hit function

    if an object is intercepted, that determines the color of the pixel.

    else
    we use a default sky color for the pixel
*/

t_vec3      color(t_ray *ray, t_hit_list *world)
{
    t_hit_record    rec;

    if (hitable_list_hit(ray, 0.0, MAXFLOAT, &rec, world))  //this hit function is different. This one will cycle thru the linked list
    {
        return (v_mult_f(0.5, new_vec(x(&rec.normal), y(&rec.normal) + 1.0, z(&rec.normal) + 1.0)));
    }
    //else      use sky coloring
    t_vec3 unit_direction;
    float t;
    t_vec3  sky;
    t_vec3  white;

    white = new_vec(1.0, 1.0, 1.0);
    white = v_mult_f((1.0 - t), white);

    sky = new_vec(0.5, 0.7, 1.0);
    sky = v_mult_f(t, sky);
    unit_direction = unit_vector(direction(*ray));    
    t = (0.5*y(&unit_direction) + 1.0);
    return (v_plus_v(white, sky));
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