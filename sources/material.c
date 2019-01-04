#include "../includes/ray_tracer.h"

//for lambertian
int     lambertian_scatter(t_ray *ray,  t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, void *ptr)
{
    t_lambertian    *object;
    t_vec3          target;

    (void)ray;
    object = ptr;
    target = v_plus_v(rec.p, rec.normal);
    target = v_plus_v(target, random_in_sphere());
    scattered->A = rec.p;
    scattered->B = v_minus_v(target, rec.p);

    copy_vector(attenuation, &object->albedo);
    return (1);
}

t_vec3  reflect(t_vec3 v, t_vec3 n)
{
    t_vec3  temp;
    float   nbr;

    nbr = (float)(2.0) * dot(v, n);
    temp = v_mult_f(nbr, n);
    temp = v_minus_v(v, temp);
    return (temp);
}

int     metal_scatter(t_ray *ray,  t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, void *ptr)
{
    t_vec3  reflected;
    t_metal *object;

    object = ptr;
    reflected = reflect(unit_vector(direction(*ray)), rec.normal);
    scattered->A = rec.p;
    scattered->B = reflected;
    copy_vector(attenuation, &object->albedo);
    if (dot(direction(*scattered), rec.normal) > 1)
        return (1);
    return (0);
}