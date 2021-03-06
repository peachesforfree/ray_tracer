#include "../includes/ray_tracer.h"

//for lambertian
int     lambertian_scatter(t_ray *ray,  t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered, void *ptr)
{
    t_lambertian    *object;
    t_vec3          target;

    (void)ray;
    object = ptr;
    target = v_plus_v(rec->p, rec->normal);
    target = v_plus_v(target, random_in_sphere());
    scattered->A = rec->p;
    scattered->B = v_minus_v(target, rec->p);

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

int     metal_scatter(t_ray *ray,  t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered, void *ptr)
{
    t_vec3  reflected;
    t_metal *object;

    object = ptr;
    reflected = reflect(unit_vector(direction(*ray)), rec->normal);
    scattered->A = rec->p;
    scattered->B = v_plus_v(reflected, v_mult_f(object->fuzz, random_in_sphere()));
    *attenuation = object->albedo;
    if (dot(direction(*scattered), rec->normal) > 0)
        return (1);
    return (0);
}

float   schlick(float cosine, float ref_idx)
{
    float r0;
    
    r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
    r0 = r0 * r0;
    return ((r0 + (1.0 - r0)) * powf((1.0 - cosine), 5));
}

int     refract(t_vec3 v, t_vec3 *n, float ni_over_nt, t_vec3 *refracted)
{
    t_vec3  uv = unit_vector(v);
    float dt = dot(uv, *n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0)
    {
        *refracted = v_mult_f(ni_over_nt, v_mult_f(dt, v_minus_v(*n, uv)));
        *refracted = v_minus_v(*refracted, v_mult_f(sqrtf(discriminant), *n));
        return (1);
    }
    return (0);
}

int     dielectric_scatter(t_ray *ray, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered, void *ptr)
{
    t_dielectric *object = ptr;
    t_vec3 outward_normal;
    //t_vec3 reflected;
    *attenuation = new_vec(1.0, 1.0, 1.0);

    float   ni_over_nt;
    t_vec3  refracted;
    float   reflect_prob;
    float   cosine;

    if (dot(direction(*ray), rec->normal) > 0.0)
    {
        outward_normal = v_mult_f(-1.0, rec->normal);
        ni_over_nt = object->ref_idx;
        cosine = object->ref_idx * dot(direction(*ray), rec->normal) / length(direction(*ray));
    }
    else
    {
        outward_normal = rec->normal;
        ni_over_nt = (float)(1.0 / object->ref_idx);
        cosine = (-1.0 * dot(direction(*ray), rec->normal)) / length(direction(*ray));
    }
    if (refract(direction(*ray), &outward_normal, ni_over_nt, &refracted))
    {
        reflect_prob = schlick(cosine, object->ref_idx);
    }
    else
    {
        reflect_prob = 1.0;
    }
    if ((float)(drand48()) < reflect_prob)
    {
        scattered->A = rec->p;
        scattered->B = reflect(direction(*ray), rec->normal);;
    }
    else
    {
        scattered->A = rec->p;
        scattered->B = refracted;
    }
    return (1);
}