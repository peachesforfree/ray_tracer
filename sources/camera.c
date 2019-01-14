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
    r.B = v_minus_v(r.B, cam->origin);
    return (r);
}

t_camera    init_camera(t_vec3 look_from, t_vec3 look_at, t_vec3 vert_up,  float vfov, float aspect)
{
    t_camera    c;
    t_vec3      u, v, w;

    float       theta = vfov * (float)(M_PI/180);
    float       half_height = (float)(tan(theta / 2));
    float       half_width = aspect * half_height;
    
    c.origin = look_from;
    w = unit_vector(v_minus_v(look_from, look_at));
    u = unit_vector(cross(vert_up, w));
    v = cross(w, u);
    c.lower_left_corner = c.origin;
    c.lower_left_corner = v_minus_v(c.lower_left_corner, v_mult_f(half_width, u));
    //c.lower_left_corner = v_mult_v(c.lower_left_corner, u);
    //c.lower_left_corner = v_minus_f(-half_height, c.lower_left_corner);
    c.lower_left_corner = v_minus_v(c.lower_left_corner, v_mult_f(half_height, v));
    c.lower_left_corner = v_minus_v(c.lower_left_corner, w);
    //c.lower_left_corner = v_minus_v(v_minus_v(c.origin, v_minus_v(v_mult_f(-half_width, u), v_mult_f(-half_height, v))), w);
    c.horizontal = v_mult_f((2 * half_width), u);
    c.vertical = v_mult_f((2 * half_height), v);
    
    return (c);
}