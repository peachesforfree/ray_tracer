#include "../includes/ray_tracer.h"

float        hit_sphere(t_vec3 *center, float radius, t_ray *r)
{
    t_vec3  oc;
    float   a;
    float   b;
    float   c;
    float   discriminant;

    oc = v_minus_v(origin(*r), *center);
    a = dot(direction(*r), direction(*r));
    b = 2.0 * dot(oc, direction(*r));
    c = dot(oc, oc) - radius * radius;
    discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
        return (-1);
    return ((-b - sqrtf(discriminant)) / (2.0 * a));
}

t_vec3      new_vec(float a, float b, float c)
{
    t_vec3  result;

    result.e[0] = a;
    result.e[1] = b;
    result.e[2] = c;
    return(result);
}


t_vec3      color(t_ray *ray)
{
    t_vec3  unit_direction;
    float   t;
    t_vec3  white;
    t_vec3  sky;
    t_vec3  N;
    t_vec3  shade;
    t_vec3  temp;

    temp = new_vec(0.0, 0.0, -1);
    t = hit_sphere(&temp, 0.5, ray);
    if (t > 0.0)
    {
        N = unit_vector(v_minus_v(point_at_parameter(*ray, t), new_vec(0, 0, -1)));
        shade = new_vec(x(&N)+1, y(&N)+1, z(&N)+1);
        return (v_mult_f(0.5, shade));
    }
    unit_direction = unit_vector(direction(*ray));
    t = 0.5 * (y(&unit_direction) + 1.0);
    
    white = v_mult_f((1.0 - t), new_vec(1.0, 1.0, 1.0));
    sky = v_mult_f(t, new_vec(0.5, 0.7, 1.0));
    return (v_plus_v(white, sky));
}


int main(void)
{
    t_mlx   mlx;
    
    //hit_list.content = new_sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3));
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
            
            pixel = color(&r);
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