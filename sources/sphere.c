#include "../includes/ray_tracer.h"

/*
typedef struct      s_sphere
{
    t_vec3      center;
    float       radius;
}                   t_sphere;

typedef struct      s_hit_record
{
    float   t;
    t_vec3  p;
    t_vec3  normal;
}                   t_hit_record;

*/

t_vec3  random_vec3()
{
    t_vec3  random;

    random = new_vec(drand48(), drand48(), drand48());
    random = v_mult_f(2.0, random);
    random = v_minus_v(random, new_vec(1.0, 1.0, 1.0));
    return (random);
}

t_vec3  random_in_sphere()
{
    t_vec3  s;

    s = random_vec3();
    while (squared_length(s) >= 1.0)
        s = random_vec3();
    return (s);
}

int     ft_sphere_hit(const t_ray *r, float t_min, float t_max, t_hit_record *rec, void *ptr)
{
    t_sphere *sphere;
    t_vec3 oc;
    float a;
    float b;
    float c;
    float discriminant;

    sphere = ptr;
    oc = v_minus_v(origin(*r), sphere->center);
    a = dot(direction(*r), direction(*r));
    b = dot(oc, direction(*r));
    c = dot(oc, oc) - (sphere->radius * sphere->radius);
    discriminant = (b * b) - (a * c);
    if (discriminant > 0)
    {
        float temp;
        temp = (-b - sqrtf((b * b) - (a * c))) / a;         //optimize ... replace (b * b - a * c) with discriminant variable?
        if (temp < t_max && temp > t_min)
        {
            rec->t = temp;
            rec->p = point_at_parameter(*r, rec->t);
            rec->normal = v_div_f(sphere->radius, v_minus_v(rec->p, sphere->center));
            return (1);
        }
        temp = (-b + sqrtf((b * b) - (a * c))) / a;
        if (temp < t_max && temp > t_min)
        {
            rec->t = temp;
            rec->p = point_at_parameter(*r, rec->t);
            rec->normal = v_div_f(sphere->radius, v_minus_v(rec->p, sphere->center));
            return (1);
        }
    }
    return (0);
}

t_sphere    *alloc_sphere(t_vec3 center, float radius)
{
    t_sphere    *result;

    result = (t_sphere*)ft_memalloc(sizeof(t_sphere));
    copy_vector(&result->center, &center);
    result->radius = radius;
    return(result);
}