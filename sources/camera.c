#include "../includes/ray_tracer.h"

// typedef struct      s_camera
// {
//     t_vec3  origin;
//     t_vec3  lower_left_corner;
//     t_vec3  horizontal;
//     t_vec3  vertical;
// }                   t_camera;

t_ray    get_ray(t_camera *cam, float u, float v)
{
    t_ray   r;

    r.A = cam->origin;
    r.B = cam->lower_left_corner;
    r.B = v_plus_v(r.B, v_mult_f(u, cam->horizontal));
    r.B = v_plus_v(r.B, v_mult_f(v, cam->vertical));
    r.B = v_minus_v(cam->origin, r.B);
    return (r);
}

t_camera    init_camera(void)
{
    t_camera    c;
    //set_vec(&c.lower_left_corner, -2.0, -1.0, -1.0);
    c.lower_left_corner = new_vec(-2.0, -1.0, -1.0);
    // set_vec(&c.horizontal, 4.0, 0.0, 0.0);
    c.horizontal = new_vec(4.0, 0.0, 0.0);
    // set_vec(&c.vertical, 0.0, 2.0, 0.0);
    c.vertical = new_vec(0.0, 2.0, 0.0);
    // set_vec(&c.origin, 0.0, 0.0, 0.0);
    c.origin = new_vec(0.0, 2.0, 0.0);
    return (c);
}